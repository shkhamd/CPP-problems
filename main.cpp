/*
N = given Number
n = number of root
a = assumed root
e = amount of error in assumed root 'a'

So,
N = (a+e)^n

Using binomial expansion formula, we can derive 'e' as the following equation:

    e = (N-a^n)/[na^(n-1)]

here,

1. estimate an initial value of 'a'
    tips:
        1.1 Calculate biggest-immediate-smaller integer-root 'x' for which x^n<N
        and also calculate smallest-immediate-bigger integer-root 'y' for which y^n>N
        e.g if N = 67 and we want to find its 5th root then n=5, so x = 2 since 2^5=32
        and y=3 since 3^5=243.

        Since 67 lies between 32 and 243 which is 5th power of 2 and 3, so there is no other
        integer which has its 5th power that lies between 32 and 243.

        So, now we know, 5th root of 67 will be some float number that lies between 2 and 3.
        We will assume its 2.3 or 2.4 or something similar. the more accurate our assumption is,
        the less calculation we need to perform.

        Now for the fraction part of the assumed root, we will use the following formula:

        (N-x^n)/(y^n-x^n)
        so the final assumed root 'a' is:

        a = x + (N-x^n)/(y^n-x^n)

2. Now that we have assumed 'a', we have to calculate how much we are off from the actual n-th root of N
   by calculating amount of error 'e'.

   for this we use the following formula (for details: https://www.youtube.com/watch?v=6ArrxekYR2U )

       e = (N-a^n)/[na^(n-1)]

3. we have assumed an initial 'a' very close to the actual root, we also figured how much we are off
    from an approximated actual 'a' by calculating 'e'
    Now we will update the initial root 'a' using this:

    a(new) = a(old) + e

4. repeat process 2 and 3 until e becomes very close to zero.
    for that assume an accuracy factor 'C'
        lets say 'C' = 0.00001
    so we will stop when e<=C condition occurs in this repeating process.

*/

#include <iostream>
using namespace std;

double power(double base, int pwr)
{
    double result = 1;
    for(int i = 1; i<= pwr; i++)
    {
        result = result * base;
    }
    return result;
}


// for sake of time pow from MATH.H is used, use your own power function here instead
// during submission
//double power(double base, int pwr){ return (double) pow(base, pwr);}

//estimates the the root 'a' for the first time with few
// numerical tricks to minimize the error and thus calculation overhead
double assume_a(int N, int n)
{
    int x = 0, y;
    while (power(x, n) <= N)
        x++;
    y = x--;
    //cout<<"x = "<<x<<endl<<"y = "<<y<<endl;
    double a = (double) x + ((double) N - power(x,n))/(power(y,n) - power(x,n));
    return a;
}

// calculate 'e' using e = (N-a^n)/[na^(n-1)]
// e should become very small with each iteration
double estimate_error(int N, int n, double a)
{
    double e = ((double)N - (double)power(a, n)) / (((double)n)*power(a, n-1));
    cout<<"[e] = "<<e<<endl;
    return e;
}

//estimate the new a using a(new) = a(old) + e
double estimate_a(double old_a, double error)
{
    return old_a+error;
}

double approximate_root(int N, int n)
{
    double C = 0.00001; // correctness constant
    double a = assume_a(N, n);
    double e = estimate_error(N, n, a);
    int iter = 0;

    do
    {
        a = estimate_a(a, e);
        e = estimate_error(N, n, a);
        //cout<<"["<<iter<<"] a = "<<a<<endl;
        iter++;
    } while(e>C || e<(-C));

    return a;
}
int main()
{
    int N, n;
    cout << "Give N: ";
    cin>>N;
    cout << "Give n: ";
    cin>>n;
    cout<<"\n\nFINAL ROOT = "<<approximate_root(N,n)<<endl;
    return 0;
}
