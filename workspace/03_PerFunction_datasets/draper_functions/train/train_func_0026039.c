ProdIntObj ( Obj n, Obj op )
{
  Obj                 res = 0;
  UInt                i, k;
  TypLimb             l;


  if      ( TNUM_OBJ(n) == T_INT && INT_INTOBJ(n) ==  0 ) {
    res = ZERO( op );
  }


  else if ( TNUM_OBJ(n) == T_INT && INT_INTOBJ(n) ==  1 ) {
    if (IS_MUTABLE_OBJ(op))
      res = SUM(ZERO(op),op);
    else
      res = op;
  }


  else if ( TNUM_OBJ(n) == T_INT && INT_INTOBJ(n) == -1 ) {
    res = AINV( op );
  }


  else if ( ( TNUM_OBJ(n) == T_INT && INT_INTOBJ(n) <  -1 )
            || IS_INTNEG(n) ) {
    res = AINV( op );
    if ( res == Fail ) {
      return ErrorReturnObj(
                            "Operations: <obj> must have an additive inverse",
                            0L, 0L,
                            "you can supply an inverse <inv> for <obj> via 'return <inv>;'" );
    }
    res = PROD( AINV( n ), res );
  }


  else if ( TNUM_OBJ(n) == T_INT && INT_INTOBJ(n) >   1 ) {
    res = 0;
    k = 1L << (NR_SMALL_INT_BITS+1);
    l = INT_INTOBJ(n);
    while ( 1 < k ) {
      res = (res == 0 ? res : SUM( res, res ));
      k = k / 2;
      if ( k <= l ) {
        res = (res == 0 ? op : SUM( res, op ));
        l = l - k;
      }
    }
  }


  else if ( TNUM_OBJ(n) == T_INTPOS ) {
    res = 0;
    for ( i = SIZE_INT(n); 0 < i; i-- ) {
      k = 8*sizeof(TypLimb);
      l = ((TypLimb*) ADDR_INT(n))[i-1];
      while ( 0 < k ) {
        res = (res == 0 ? res : SUM( res, res ));
        k--;
        if ( (l >> k) & 1 ) {
          res = (res == 0 ? op : SUM( res, op ));
        }
      }
    }
  }


  return res;
}
