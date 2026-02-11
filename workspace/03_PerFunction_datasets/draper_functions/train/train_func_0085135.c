mpi_div_int( mpi *Q, mpi *R, mpi *A, int b )
{
    mpi _B;
    t_int p[1];

    p[0] = ( b < 0 ) ? -b : b;
    _B.s = ( b < 0 ) ? -1 : 1;
    _B.n = 1;
    _B.p = p;

    return( mpi_div_mpi( Q, R, A, &_B ) );
}
