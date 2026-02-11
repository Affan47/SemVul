FuncINSTALL_METHOD_ARGS (
    Obj                 self,
    Obj                 oper,
    Obj                 func )
{

    if ( ! IS_FUNC(oper) ) {
        ErrorQuit( "<oper> must be a function (not a %s)",
                   (Int)TNAM_OBJ(oper), 0L );
    }
    if ( (REREADING != True) &&
         (HDLR_FUNC(oper,0) != (ObjFunc)DoUninstalledOperationArgs) ) {
        ErrorQuit( "operation already installed",
                   0L, 0L );
        return 0;
    }
    if ( ! IS_FUNC(func) ) {
        ErrorQuit( "<func> must be a function (not a %s)",
                   (Int)TNAM_OBJ(func), 0L );
        return 0;
    }
    if ( IS_OPERATION(func) ) {
        ErrorQuit( "<func> must not be an operation", 0L, 0L );
        return 0;
    }


    InstallMethodArgs( oper, func );
    return 0;
}
