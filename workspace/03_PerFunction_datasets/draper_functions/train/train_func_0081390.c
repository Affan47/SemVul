DoVerboseOperation3Args (
    Obj                 oper,
    Obj                 arg1,
    Obj                 arg2,
    Obj                 arg3 )
{
    Obj                 res;
    Obj                 kind1;
    Obj                 kind2;
    Obj                 kind3;
    Obj                 method;
    Int                 i;


    kind1 = TYPE_OBJ_FEO( arg1 );
    kind2 = TYPE_OBJ_FEO( arg2 );
    kind3 = TYPE_OBJ_FEO( arg3 );


    method = CALL_4ARGS( VMethod3Args, oper, kind1, kind2, kind3 );
    while (method == Fail)
      {
        Obj arglist[3];
        arglist[0] = arg1;
        arglist[1] = arg2;
        arglist[2] = arg3;
        method = CallHandleMethodNotFound( oper, 3, arglist, 1, 0, INTOBJ_INT(0));
      }

    if ( method == 0 )  {
        ErrorQuit( "no method returned", 0L, 0L );
    }


    res = CALL_3ARGS( method, arg1, arg2, arg3 );


    if ( res == TRY_NEXT_METHOD ) {
        i = 1;
        while ( res == TRY_NEXT_METHOD ) {
#ifdef COUNT_OPERS
            OperationNext++;
#endif
            method = CALL_5ARGS( NextVMethod3Args, oper, INTOBJ_INT(i),
                                 kind1, kind2, kind3 );
            while (method == Fail)
              {
                Obj arglist[3];
                arglist[0] = arg1;
                arglist[1] = arg2;
                arglist[2] = arg3;
                method = CallHandleMethodNotFound( oper, 3, arglist, 1, 0, INTOBJ_INT(i));
              }

            i++;
            res = CALL_3ARGS( method, arg1, arg2, arg3 );
        }
    }


    return res;
}
