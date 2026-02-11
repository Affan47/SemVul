UpdateCopyFopyInfo ( void )
{
    Obj                 cops;
    UInt                ncop;
    UInt                gvar;
    const Char *        name;
    Obj *               copy;


    for ( ; NCopyAndFopyDone < NCopyAndFopyGVars; NCopyAndFopyDone++ ) {
        name = CopyAndFopyGVars[NCopyAndFopyDone].name;
        copy = CopyAndFopyGVars[NCopyAndFopyDone].copy;
        gvar = GVarName(name);


        if ( CopyAndFopyGVars[NCopyAndFopyDone].isFopy ) {
            if ( ELM_PLIST( FopiesGVars, gvar ) != 0 ) {
                cops = ELM_PLIST( FopiesGVars, gvar );
            }
            else {
                cops = NEW_PLIST( T_PLIST, 0 );
                SET_ELM_PLIST( FopiesGVars, gvar, cops );
                CHANGED_BAG(FopiesGVars);
            }
        }
        else {
            if ( ELM_PLIST( CopiesGVars, gvar ) != 0 ) {
                cops = ELM_PLIST( CopiesGVars, gvar );
            }
            else {
                cops = NEW_PLIST( T_PLIST, 0 );
                SET_ELM_PLIST( CopiesGVars, gvar, cops );
                CHANGED_BAG(CopiesGVars);
            }
        }
        ncop = LEN_PLIST(cops);


        GROW_PLIST( cops, ncop+1 );
        SET_LEN_PLIST( cops, ncop+1 );
        SET_ELM_PLIST( cops, ncop+1, (Obj)copy );
        CHANGED_BAG(cops);


        if ( CopyAndFopyGVars[NCopyAndFopyDone].isFopy ) {
            if ( VAL_GVAR(gvar) != 0 && IS_FUNC(VAL_GVAR(gvar)) ) {
                *copy = VAL_GVAR(gvar);
            }
            else if ( VAL_GVAR(gvar) != 0 ) {
                *copy = ErrorMustEvalToFuncFunc;
            }
            else {
                *copy = ErrorMustHaveAssObjFunc;
            }
        }
        else {
            *copy = VAL_GVAR(gvar);
        }
    }
}
