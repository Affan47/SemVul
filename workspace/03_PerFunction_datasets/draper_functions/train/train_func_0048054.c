cfftb( N, F, T )
    int N;
    COMPLEX *F;
    COMPLEX *T;
{
    int logN;
    int k;

    if ( F != T ) {
        for( k = 0; k < N; k++ ) T[k].Real = F[k].Real;
        }
    for( k = 0; k < N; k++ ) T[k].Imag = -F[k].Imag;
    cfftf( N, T, T );
    for( k = 0; k < N; k++ ) T[k].Imag = -T[k].Imag;
}
