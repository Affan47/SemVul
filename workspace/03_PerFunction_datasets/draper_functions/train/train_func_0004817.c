FuncZ (
    Obj                 self,
    Obj                 q )
{
    FF                  ff;
    UInt                p;
    UInt                d;
    UInt                r;


    if ( (TNUM_OBJ(q) == T_INT && (INT_INTOBJ(q) > 65536)) ||
         (TNUM_OBJ(q) == T_INTPOS))
      return CALL_1ARGS(ZOp, q);

    if ( TNUM_OBJ(q)!=T_INT || INT_INTOBJ(q)<=1 ) {
        q = ErrorReturnObj(
            "Z: <q> must be a positive prime power (not a %s)",
            (Int)TNAM_OBJ(q), 0L,
            "you can replace <q> via 'return <q>;'" );
        return FuncZ( self, q );
    }


    if ( INT_INTOBJ(q) % 2 == 0 ) {
        p = 2;
    }
    else {
        p = 3;
        while ( INT_INTOBJ(q) % p != 0 ) {
            p += 2;
        }
    }
    d = 1;
    r = p;
    while ( r < INT_INTOBJ(q) ) {
        d = d + 1;
        r = r * p;
    }
    if ( r != INT_INTOBJ(q) ) {
        q = ErrorReturnObj(
            "Z: <q> must be a positive prime power (not a %s)",
            (Int)TNAM_OBJ(q), 0L,
            "you can replace <q> via 'return <q>;'" );
        return FuncZ( self, q );
    }


    ff = FiniteField( p, d );


    return NEW_FFE( ff, (p == 2 && d == 1 ? 1 : 2) );
}
