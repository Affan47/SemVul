DoVerboseOperation2Args (
    Obj                 oper,
    Obj                 arg1,
    Obj                 arg2 )
{
    Obj                 res;
    Obj                 kind1;
    Obj                 kind2;
    Obj                 method;
    Int                 i;


    kind1 = TYPE_OBJ_FEO( arg1 );
    kind2 = TYPE_OBJ_FEO( arg2 );


    method = CALL_3ARGS( VMethod2Args, oper, kind1, kind2 );
    while (method == Fail)
      {
        Obj arglist[2];
        arglist[0] = arg1;
        arglist[1] = arg2;
        method = CallHandleMethodNotFound( oper, 2, arglist, 1, 0, INTOBJ_INT(0));
      }

    if ( method == 0 )  {
        ErrorQuit( "no method returned", 0L, 0L );
    }


    res = CALL_2ARGS( method, arg1, arg2 );


    if ( res == TRY_NEXT_METHOD ) {
        i = 1;
        while ( res == TRY_NEXT_METHOD ) {
#ifdef COUNT_OPERS
            OperationNext++;
#endif
            method = CALL_4ARGS( NextVMethod2Args, oper, INTOBJ_INT(i),
                                 kind1, kind2 );
            while (method == Fail)
              {
                Obj arglist[2];
                arglist[0] = arg1;
                arglist[1] = arg2;
                method = CallHandleMethodNotFound( oper, 2, arglist, 1, 0, INTOBJ_INT(i));
              }

            i++;
            res = CALL_2ARGS( method, arg1, arg2 );
        }
    }


    return res;
}
