PowFFEFFE (
    Obj                 opL,
    Obj                 opR )
{

    if ( CHAR_FF( FLD_FFE(opL) ) != CHAR_FF( FLD_FFE(opR) ) ) {
        opR = ErrorReturnObj(
          "FFE operations: characteristic of conjugating element must be %d",
          (Int)CHAR_FF(FLD_FFE(opL)), 0L,
          "you can replace conjugating element <elt> via 'return <elt>;'" );
        return POW( opL, opR );
    }


    return opL;
}
