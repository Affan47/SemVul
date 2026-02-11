mpi_gen_prime( mpi *X, size_t nbits, int dh_flag,
                   int (*f_rng)(void *, unsigned char *, size_t),
                   void *p_rng )
{
    int ret;
    size_t k, n;
    t_uint r;
    mpi Y;

    if( nbits < 3 || nbits > POLARSSL_MPI_MAX_BITS )
        return( POLARSSL_ERR_MPI_BAD_INPUT_DATA );

    mpi_init( &Y );

    n = BITS_TO_LIMBS( nbits );

    MPI_CHK( mpi_fill_random( X, n * ciL, f_rng, p_rng ) );

    k = mpi_msb( X );
    if( k < nbits ) MPI_CHK( mpi_shift_l( X, nbits - k ) );
    if( k > nbits ) MPI_CHK( mpi_shift_r( X, k - nbits ) );

    X->p[0] |= 3;

    if( dh_flag == 0 )
    {
        while( ( ret = mpi_is_prime( X, f_rng, p_rng ) ) != 0 )
        {
            if( ret != POLARSSL_ERR_MPI_NOT_ACCEPTABLE )
                goto cleanup;

            MPI_CHK( mpi_add_int( X, X, 2 ) );
        }
    }
    else
    {


        MPI_CHK( mpi_mod_int( &r, X, 3 ) );
        if( r == 0 )
            MPI_CHK( mpi_add_int( X, X, 8 ) );
        else if( r == 1 )
            MPI_CHK( mpi_add_int( X, X, 4 ) );


        MPI_CHK( mpi_copy( &Y, X ) );
        MPI_CHK( mpi_shift_r( &Y, 1 ) );

        while( 1 )
        {


            if( ( ret = mpi_check_small_factors(  X         ) ) == 0 &&
                ( ret = mpi_check_small_factors( &Y         ) ) == 0 &&
                ( ret = mpi_miller_rabin(  X, f_rng, p_rng  ) ) == 0 &&
                ( ret = mpi_miller_rabin( &Y, f_rng, p_rng  ) ) == 0 )
            {
                break;
            }

            if( ret != POLARSSL_ERR_MPI_NOT_ACCEPTABLE )
                goto cleanup;


            MPI_CHK( mpi_add_int(  X,  X, 12 ) );
            MPI_CHK( mpi_add_int( &Y, &Y, 6  ) );
        }
    }

cleanup:

    mpi_free( &Y );

    return( ret );
}
