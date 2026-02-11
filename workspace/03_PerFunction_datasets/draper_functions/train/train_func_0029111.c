mpi_mod_mpi( mpi *R, const mpi *A, const mpi *B )
{
    int ret;

    if( mpi_cmp_int( B, 0 ) < 0 )
        return POLARSSL_ERR_MPI_NEGATIVE_VALUE;

    MPI_CHK( mpi_div_mpi( NULL, R, A, B ) );

    while( mpi_cmp_int( R, 0 ) < 0 )
      MPI_CHK( mpi_add_mpi( R, R, B ) );

    while( mpi_cmp_mpi( R, B ) >= 0 )
      MPI_CHK( mpi_sub_mpi( R, R, B ) );

cleanup:

    return( ret );
}
