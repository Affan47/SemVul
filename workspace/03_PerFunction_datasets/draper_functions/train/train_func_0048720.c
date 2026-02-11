ecp_mod_koblitz( mpi *N, t_uint *Rp, size_t p_limbs,
                                   size_t adjust, size_t shift, t_uint mask )
{
    int ret;
    size_t i;
    mpi M, R;
    t_uint Mp[P_KOBLITZ_MAX + P_KOBLITZ_R];

    if( N->n < p_limbs )
        return( 0 );


    R.s = 1;
    R.p = Rp;
    R.n = P_KOBLITZ_R;


    M.s = 1;
    M.p = Mp;


    M.n = N->n - ( p_limbs - adjust );
    if( M.n > p_limbs + adjust )
        M.n = p_limbs + adjust;
    memset( Mp, 0, sizeof Mp );
    memcpy( Mp, N->p + p_limbs - adjust, M.n * sizeof( t_uint ) );
    if (shift != 0 )
        MPI_CHK( mpi_shift_r( &M, shift ) );
    M.n += R.n - adjust;


    if (mask != 0 )
        N->p[p_limbs - 1] &= mask;
    for( i = p_limbs; i < N->n; i++ )
        N->p[i] = 0;


    MPI_CHK( mpi_mul_mpi( &M, &M, &R ) );
    MPI_CHK( mpi_add_abs( N, N, &M ) );


    M.n = N->n - ( p_limbs - adjust );
    if( M.n > p_limbs + adjust )
        M.n = p_limbs + adjust;
    memset( Mp, 0, sizeof Mp );
    memcpy( Mp, N->p + p_limbs - adjust, M.n * sizeof( t_uint ) );
    if (shift != 0 )
        MPI_CHK( mpi_shift_r( &M, shift ) );
    M.n += R.n - adjust;


    if (mask != 0 )
        N->p[p_limbs - 1] &= mask;
    for( i = p_limbs; i < N->n; i++ )
        N->p[i] = 0;


    MPI_CHK( mpi_mul_mpi( &M, &M, &R ) );
    MPI_CHK( mpi_add_abs( N, N, &M ) );

cleanup:
    return( ret );
}
