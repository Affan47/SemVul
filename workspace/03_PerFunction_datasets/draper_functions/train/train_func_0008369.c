mpi_write_hlp( mpi *X, int radix, char **p )
{
    int ret;
    t_int r;

    if( radix < 2 || radix > 16 )
        return( POLARSSL_ERR_MPI_BAD_INPUT_DATA );

    MPI_CHK( mpi_mod_int( &r, X, radix ) );
    MPI_CHK( mpi_div_int( X, NULL, X, radix ) );

    if( mpi_cmp_int( X, 0 ) != 0 )
        MPI_CHK( mpi_write_hlp( X, radix, p ) );

    if( r < 10 )
        *(*p)++ = (char)( r + 0x30 );
    else
        *(*p)++ = (char)( r + 0x37 );

cleanup:

    return( ret );
}
