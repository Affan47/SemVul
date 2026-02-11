PowRat (
    Obj                 opL,
    Obj                 opR )
{
    Obj                 numP, denP;
    Obj                 pow;

    CHECK_RAT(opL);

    numP = PowInt( NUM_RAT(opL), opR );
    denP = PowInt( DEN_RAT(opL), opR );


    if ( opR == INTOBJ_INT( 0L ) ) {
        pow = INTOBJ_INT( 1L );
    }


    else if ( opR == INTOBJ_INT( 1L ) ) {
        pow = opL;
    }


    else if ( (TNUM_OBJ(opR) == T_INT && 0 < INT_INTOBJ(opR))
           || TNUM_OBJ(opR) == T_INTPOS ) {
        numP = PowInt( NUM_RAT(opL), opR );
        denP = PowInt( DEN_RAT(opL), opR );
        pow = NewBag( T_RAT, 2 * sizeof(Obj) );
        NUM_RAT(pow) = numP;
        DEN_RAT(pow) = denP;

    }


    else if ( NUM_RAT(opL) == INTOBJ_INT( 1L ) ) {
        pow = PowInt( DEN_RAT(opL), ProdInt( INTOBJ_INT(-1L), opR ) );
    }


    else if ( NUM_RAT(opL) == INTOBJ_INT( -1L ) ) {
        pow = ProdInt(PowInt(NUM_RAT(opL),ProdInt(INTOBJ_INT(-1L),opR)),
                      PowInt(DEN_RAT(opL),ProdInt(INTOBJ_INT(-1L),opR)));
    }


    else {
        numP = PowInt( DEN_RAT(opL), ProdInt( INTOBJ_INT( -1L ), opR ) );
        denP = PowInt( NUM_RAT(opL), ProdInt( INTOBJ_INT( -1L ), opR ) );
        pow  = NewBag( T_RAT, 2 * sizeof(Obj) );
        if ( (TNUM_OBJ(denP) == T_INT && 0 < INT_INTOBJ(denP))
          || TNUM_OBJ(denP) == T_INTPOS ) {
            NUM_RAT(pow) = numP;
            DEN_RAT(pow) = denP;
        }
        else {
            NUM_RAT(pow) = ProdInt( INTOBJ_INT( -1L ), numP );
            DEN_RAT(pow) = ProdInt( INTOBJ_INT( -1L ), denP );
        }

    }


    CHECK_RAT(pow);
    return pow;
}
