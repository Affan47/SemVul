ecp_mul_comb_core( const ecp_group *grp, ecp_point *R,
                              const ecp_point T[], unsigned char t_len,
                              const unsigned char x[], size_t d,
                              int (*f_rng)(void *, unsigned char *, size_t),
                              void *p_rng )
{
    int ret;
    ecp_point Txi;
    size_t i;

    ecp_point_init( &Txi );


    i = d;
    MPI_CHK( ecp_select_comb( grp, R, T, t_len, x[i] ) );
    MPI_CHK( mpi_lset( &R->Z, 1 ) );
    if( f_rng != 0 )
        MPI_CHK( ecp_randomize_jac( grp, R, f_rng, p_rng ) );

    while( i-- != 0 )
    {
        MPI_CHK( ecp_double_jac( grp, R, R ) );
        MPI_CHK( ecp_select_comb( grp, &Txi, T, t_len, x[i] ) );
        MPI_CHK( ecp_add_mixed( grp, R, R, &Txi ) );
    }

cleanup:
    ecp_point_free( &Txi );

    return( ret );
}
