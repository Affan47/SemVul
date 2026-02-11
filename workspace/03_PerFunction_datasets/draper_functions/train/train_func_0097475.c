BitReverseArray( N, T )
    int N;
    COMPLEX *T;
{
    COMPLEX swap;

    int i;
    int j;

    int k;
    int n;

    int logN;

    log2( logN, N );
    logN--;

    for( k = 0; k < N; k++ ) {
        BitReverse( n, k, logN );
        if ( n > k ) {
            swap = T[k];
            T[k] = T[n];
            T[n] = swap;
            }
       }
}
