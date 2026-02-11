SumFFEInt (
    Obj                 opL,
    Obj                 opR )
{
    FFV                 vL, vR, vX;
    FF                  fX;
    Int                 pX;
    FF*                 sX;


    fX = FLD_FFE( opL );
    pX = CHAR_FF( fX );
    sX = SUCC_FF( fX );


    vX = ((INT_INTOBJ( opR ) % pX) + pX) % pX;
    if ( vX == 0 ) {
        vR = 0;
    }
    else {
        vR = 1;
        for ( ; 1 < vX; vX-- )  vR = sX[vR];
    }


    vL = VAL_FFE( opL );


    vX = SUM_FFV( vL, vR, sX );
    return NEW_FFE( fX, vX );
}
