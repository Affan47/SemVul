ecp_mod_p192( mpi *N )
{
    int ret;
    t_uint c = 0;
    t_uint *p, *end;


    MPI_CHK( mpi_grow( N, 6 * WIDTH ) );

    p = N->p;
    end = p + N->n;

    ADD( 3 ); ADD( 5 );             NEXT;
    ADD( 3 ); ADD( 4 ); ADD( 5 );   NEXT;
    ADD( 4 ); ADD( 5 );             LAST;

cleanup:
    return( ret );
}
