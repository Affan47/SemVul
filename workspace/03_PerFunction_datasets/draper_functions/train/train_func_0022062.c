IntrIsbDVar (
    UInt                dvar,
    UInt                depth )
{
    Obj                 val;
    Obj                 currLVars;


    if ( IntrReturning > 0 ) { return; }
    if ( IntrIgnoring  > 0 ) { return; }


    currLVars = CurrLVars;
    SWITCH_TO_OLD_LVARS( ErrorLVars );
    SWITCH_TO_OLD_LVARS( ErrorLVars );
    while (depth--)
      SWITCH_TO_OLD_LVARS( PTR_BAG(CurrLVars) [2] );
    val = OBJ_HVAR( dvar );
    SWITCH_TO_OLD_LVARS( currLVars  );


    PushObj( (val != 0 ? True : False) );
}
