cfftf3D( L, M, N, T, F )
    int L,M,N;
    COMPLEX *T;
    COMPLEX *F;
{
    COMPLEX *W;

    int j;
    int k;
    int n;

    W = (COMPLEX *)malloc( L * sizeof( COMPLEX ) );

    for( k = 0; k < L; k++ ) cfftf2D( M, N, &T[k*M*N], &F[k*M*N] );

    for( j = 0; j < M * N; j++ ) {
        for( k = 0, n = j; k < L; k++, n += M * N ) W[k] = F[n];

        cfftf( L, W, W );

        for( k = 0, n = j; k < L; k++, n += M * N ) F[n] = W[k];
        }

    free( W );
}
