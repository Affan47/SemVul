cfftfND( N, D, T, F )
    int  N;
    int *D;
    COMPLEX *T;
    COMPLEX *F;
{
    COMPLEX *W;

    int TotN;
    int WN;

    int i;
    int j;
    int k;
    int l;
    int m;

    int S[32];
    int P[32];

    WN = D[0];
    TotN = 1;
    for( i = 0; i < N; i++ ) {
        if ( D[i] > WN ) WN = D[i];
        S[i]  = TotN;
        TotN *= D[i];
        }

    W = (COMPLEX *)malloc( WN * sizeof( COMPLEX ) );

    if ( F != T )
        for( i = 0; i < TotN; i++ )
            F[i] = T[i];

    for( i = 0; i < N; i++ ) {

        for( j = 0; j < N; j++ ) P[j] = 0;

        k = 0;
        for( j = 0; j < TotN / D[i]; j++ ) {

            if ( j != 0 )
                for( l = 0; l < N; l++ )
                    if ( l != i ) {
                        P[l]++;
                        k += S[l];
                        if ( P[l] == D[l] ) {
                            k -= S[l + 1];
                            P[l] = 0;
                        } else {
                            break;
                            }
                        }

            for( l = 0, m = k; l < D[i]; l++, m += S[i] ) W[l] = F[m];

            cfftf( D[i], W, W );

            for( l = 0, m = k; l < D[i]; l++, m += S[i] ) F[m] = W[l];
            }
        }

    free( W );
}
