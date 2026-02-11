mpi_write_file( char *p, mpi *X, int radix, FILE *fout )
{
    int n, ret;
    size_t slen;
    size_t plen;
    char s[1024];

    n = sizeof( s );
    memset( s, 0, n );
    n -= 2;

    MPI_CHK( mpi_write_string( X, radix, s, (int *) &n ) );

    if( p == NULL ) p = "";

    plen = strlen( p );
    slen = strlen( s );
    s[slen++] = '\r';
    s[slen++] = '\n';

    if( fout != NULL )
    {
        if( fwrite( p, 1, plen, fout ) != plen ||
            fwrite( s, 1, slen, fout ) != slen )
            return( POLARSSL_ERR_MPI_FILE_IO_ERROR );
    }
    else
        printf( "%s%s", p, s );

cleanup:

    return( ret );
}
