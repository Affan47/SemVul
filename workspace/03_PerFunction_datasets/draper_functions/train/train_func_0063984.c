DoFailXargs (
    Obj                 self,
    Obj                 args )
{
    Obj                 argx;
    argx = ErrorReturnObj(
        "Function: number of arguments must be %d (not %d)",
        (Int)NARG_FUNC( self ), LEN_LIST( args ),
        "you can replace the argument list <args> via 'return <args>;'" );
    return FuncCALL_FUNC_LIST( (Obj)0, self, argx );
}
