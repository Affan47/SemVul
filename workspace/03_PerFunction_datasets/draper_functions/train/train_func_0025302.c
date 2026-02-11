mpi_read_binary( mpi *X, const unsigned char *buf, size_t buflen )
{
    int ret;
    size_t i, j, n;

    for( n = 0; n < buflen; n++ )
        if( buf[n] != 0 )
            break;

    MPI_CHK( mpi_grow( X, CHARS_TO_LIMBS( buflen - n ) ) );
    MPI_CHK( mpi_lset( X, 0 ) );

    for( i = buflen, j = 0; i > n; i--, j++ )
        X->p[j / ciL] |= ((t_uint) buf[i - 1]) << ((j % ciL) << 3);

cleanup:

    return( ret );
}
