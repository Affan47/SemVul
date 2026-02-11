DoConstructor0Args (
    Obj                 oper )
{
    Obj                 res;
    Obj *               cache;
    Obj                 method;
    Int                 i;
    Obj                prec;


    cache = 1+ADDR_OBJ( CacheOper( oper, 0 ) );
    prec = INTOBJ_INT(-1);

    do {

      prec = (Obj)(((Int)prec) +4);
      method = 0;


      if (prec < INTOBJ_INT(CACHE_SIZE))
        {
          for (i = 0;  i < 2*CACHE_SIZE; i+= 2) {
            if (  cache[i] != 0 && cache[i+1] == prec) {
              method = cache[i];
#ifdef COUNT_OPERS
              OperationHit++;
#endif
              break;
            }
          }
        }


      if (!method)
        {
          if (prec == INTOBJ_INT(0))
            method = CALL_1ARGS( Constructor0Args, oper );
          else
            method = CALL_2ARGS( NextConstructor0Args, oper, prec );

          while (method == Fail)
            method = CallHandleMethodNotFound( oper, 0, (Obj *)0, 0, 1, prec);


          if (method && prec < INTOBJ_INT(CACHE_SIZE))
            {
              cache = 1+ADDR_OBJ( CACHE_OPER( oper, 0 ) );
              cache[2*CacheIndex] = method;
              cache[2*CacheIndex+1] = prec;
              CacheIndex = (CacheIndex + 1) % CACHE_SIZE;
              CHANGED_BAG(CACHE_OPER(oper,0));
            }
#ifdef COUNT_OPERS
          OperationMiss++;
#endif
        }
      if ( !method )  {
        ErrorQuit( "no method returned", 0L, 0L );
      }


      res = CALL_0ARGS( method );
    }
    while (res == TRY_NEXT_METHOD );


    return res;
}
