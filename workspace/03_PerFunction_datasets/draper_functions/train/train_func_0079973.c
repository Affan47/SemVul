mpi_init( mpi *X, ... )
{
    va_list args;

    va_start( args, X );

    while( X != NULL )
    {
        X->s = 1;
        X->n = 0;
        X->p = NULL;

        X = va_arg( args, mpi* );
    }

    va_end( args );
}
