ecp_mod_p256( mpi *N )
{
    INIT( 256 );

    ADD(  8 ); ADD(  9 );
    SUB( 11 ); SUB( 12 ); SUB( 13 ); SUB( 14 );             NEXT;

    ADD(  9 ); ADD( 10 );
    SUB( 12 ); SUB( 13 ); SUB( 14 ); SUB( 15 );             NEXT;

    ADD( 10 ); ADD( 11 );
    SUB( 13 ); SUB( 14 ); SUB( 15 );                        NEXT;

    ADD( 11 ); ADD( 11 ); ADD( 12 ); ADD( 12 ); ADD( 13 );
    SUB( 15 ); SUB(  8 ); SUB(  9 );                        NEXT;

    ADD( 12 ); ADD( 12 ); ADD( 13 ); ADD( 13 ); ADD( 14 );
    SUB(  9 ); SUB( 10 );                                   NEXT;

    ADD( 13 ); ADD( 13 ); ADD( 14 ); ADD( 14 ); ADD( 15 );
    SUB( 10 ); SUB( 11 );                                   NEXT;

    ADD( 14 ); ADD( 14 ); ADD( 15 ); ADD( 15 ); ADD( 14 ); ADD( 13 );
    SUB(  8 ); SUB(  9 );                                   NEXT;

    ADD( 15 ); ADD( 15 ); ADD( 15 ); ADD( 8 );
    SUB( 10 ); SUB( 11 ); SUB( 12 ); SUB( 13 );             LAST;

cleanup:
    return( ret );
}
