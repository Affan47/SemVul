PowFFEInt (
    Obj                 opL,
    Obj                 opR )
{
    FFV                 vL, vX;
    Int                 vR;
    FF                  fX;
    FF*                 sX;


    fX = FLD_FFE( opL );
    sX = SUCC_FF( fX );


    vR = INT_INTOBJ( opR );


    vL = VAL_FFE( opL );


    if ( vR < 0 ) {
        if ( vL == 0 ) {
            opL = ErrorReturnObj(
                "FFE operations: <divisor> must not be zero",
                0L, 0L,
                "you can replace <divisor> via 'return <divisor>;'" );
            return POW( opL, opR );
        }
        vL = QUO_FFV( 1, vL, sX );
        vR = -vR;
    }


    if( vL == 0 ) return NEW_FFE( fX, (vR == 0 ? 1 : 0 ) );


    vR %= *sX;


    vX = POW_FFV( vL, vR, sX );
    return NEW_FFE( fX, vX );
}
