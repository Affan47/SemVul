sift( struct cookie v[], long i, long m, int mode )
    {
    long j;
    struct cookie temp;

    while( (j = 2 * (i + 1) - 1) <= m )
        {
        if( j < m && cookie_cmp( &v[ j ], &v[ j + 1 ], mode ) < 0 )
            j++;
        if( cookie_cmp( &v[ i ], &v[ j ], mode ) < 0 )
            {
            temp = v[ i ];
            v[ i ] = v[ j ];
            v[ j ] = temp;
            i = j;
            }
        else
            i = m;
        }
    }
