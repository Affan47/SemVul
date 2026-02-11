DoVerboseConstructor5Args (
    Obj                 oper,
    Obj                 arg1,
    Obj                 arg2,
    Obj                 arg3,
    Obj                 arg4,
    Obj                 arg5 )
{
    Obj                 res;
    Obj                 kind1;
    Obj                 kind2;
    Obj                 kind3;
    Obj                 kind4;
    Obj                 kind5;
    Obj                 method;
    Obj                 margs;
    Int                 i;


    while (!IS_OPERATION(arg1))
      {
        arg1 = ErrorReturnObj(
                "Constructor: the first argument must be a filter not a %s",
                (Int)TNAM_OBJ(arg1), 0L,
                "you can replace the first argument <arg1> via 'return <arg1>;'");
      }

    kind1 = FLAGS_FILT( arg1 );
    kind2 = TYPE_OBJ_FEO( arg2 );
    kind3 = TYPE_OBJ_FEO( arg3 );
    kind4 = TYPE_OBJ_FEO( arg4 );
    kind5 = TYPE_OBJ_FEO( arg5 );


    method = CALL_6ARGS( VConstructor5Args, oper, kind1, kind2, kind3, kind4,
                         kind5 );
    while (method == Fail)
      {
        Obj arglist[5];
        arglist[0] = arg1;
        arglist[1] = arg2;
        arglist[2] = arg3;
        arglist[3] = arg4;
        arglist[4] = arg5;
        method = CallHandleMethodNotFound( oper, 5, arglist, 1, 0, INTOBJ_INT(0));
      }
    if ( method == 0 )  {
        ErrorQuit( "no method returned", 0L, 0L );
    }


    res = CALL_5ARGS( method, arg1, arg2, arg3, arg4, arg5 );


    if ( res == TRY_NEXT_METHOD ) {
        i = 1;
        while ( res == TRY_NEXT_METHOD ) {
#ifdef COUNT_OPERS
            OperationNext++;
#endif
            margs = NEW_PLIST( T_PLIST, 7 );
            SET_LEN_PLIST( margs, 7 );
            SET_ELM_PLIST( margs, 1, oper );
            SET_ELM_PLIST( margs, 2, INTOBJ_INT(i) );
            SET_ELM_PLIST( margs, 3, kind1 );
            SET_ELM_PLIST( margs, 4, kind2 );
            SET_ELM_PLIST( margs, 5, kind3 );
            SET_ELM_PLIST( margs, 6, kind4 );
            SET_ELM_PLIST( margs, 7, kind5 );
            method = CALL_XARGS( NextVConstructor5Args, margs );
            while (method == Fail)
              {
                Obj arglist[5];
                arglist[0] = arg1;
                arglist[1] = arg2;
                arglist[2] = arg3;
                arglist[3] = arg4;
                arglist[4] = arg5;
                method = CallHandleMethodNotFound( oper, 5, arglist, 1, 0, INTOBJ_INT(i));
              }
            i++;
            res = CALL_5ARGS( method, arg1, arg2, arg3, arg4, arg5 );
        }
    }


    return res;
}
