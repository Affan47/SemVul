IntrUnbDVar (
    UInt                dvar,
    UInt                depth )
{
    Obj                 currLVars;


    if ( IntrReturning > 0 ) { return; }
    if ( IntrIgnoring  > 0 ) { return; }


    if ( IntrCoding > 0 ) {
        ErrorQuit( "Variable: <debug-variable-%d-%d> cannot be used here",
                   dvar >> 10, dvar & 0x3FF );
    }


    currLVars = CurrLVars;
    SWITCH_TO_OLD_LVARS( ErrorLVars );
    SWITCH_TO_OLD_LVARS( ErrorLVars );
    while (depth--)
      SWITCH_TO_OLD_LVARS( PTR_BAG(CurrLVars) [2] );
    ASS_HVAR( dvar, (Obj)0 );
    SWITCH_TO_OLD_LVARS( currLVars  );


    PushVoidObj();
}
