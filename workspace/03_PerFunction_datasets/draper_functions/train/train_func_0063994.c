FuncCALL_FUNC_LIST (
    Obj                 self,
    Obj                 func,
    Obj                 list )
{
    Obj                 result;
    Obj                 list2;
    Obj                 arg;
    UInt                i;


    while ( ! IS_SMALL_LIST( list ) ) {
        list = ErrorReturnObj(
            "CallFuncList: <list> must be a small list",
            0L, 0L,
            "you can replace <list> via 'return <list>;'" );
    }

    if (TNUM_OBJ(func) == T_FUNCTION) {


      if      ( LEN_LIST(list) == 0 ) {
        result = CALL_0ARGS( func );
      }
      else if ( LEN_LIST(list) == 1 ) {
        result = CALL_1ARGS( func, ELMV_LIST(list,1) );
      }
      else if ( LEN_LIST(list) == 2 ) {
        result = CALL_2ARGS( func, ELMV_LIST(list,1), ELMV_LIST(list,2) );
      }
      else if ( LEN_LIST(list) == 3 ) {
        result = CALL_3ARGS( func, ELMV_LIST(list,1), ELMV_LIST(list,2),
                             ELMV_LIST(list,3) );
      }
      else if ( LEN_LIST(list) == 4 ) {
        result = CALL_4ARGS( func, ELMV_LIST(list,1), ELMV_LIST(list,2),
                             ELMV_LIST(list,3), ELMV_LIST(list,4) );
      }
      else if ( LEN_LIST(list) == 5 ) {
        result = CALL_5ARGS( func, ELMV_LIST(list,1), ELMV_LIST(list,2),
                             ELMV_LIST(list,3), ELMV_LIST(list,4),
                             ELMV_LIST(list,5) );
      }
      else if ( LEN_LIST(list) == 6 ) {
        result = CALL_6ARGS( func, ELMV_LIST(list,1), ELMV_LIST(list,2),
                             ELMV_LIST(list,3), ELMV_LIST(list,4),
                             ELMV_LIST(list,5), ELMV_LIST(list,6) );
      }
      else {
        list2 = NEW_PLIST( T_PLIST, LEN_LIST(list) );
        SET_LEN_PLIST( list2, LEN_LIST(list) );
        for ( i = 1; i <= LEN_LIST(list); i++ ) {
          arg = ELMV_LIST( list, (Int)i );
          SET_ELM_PLIST( list2, i, arg );
        }
        result = CALL_XARGS( func, list2 );
      }
    } else {
      result = DoOperation2Args(self, func, list);
    }

    return result;
}
