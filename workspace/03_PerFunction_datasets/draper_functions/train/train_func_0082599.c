PostRestore (
    StructInitInfo *    module )
{
      UInt var;


    var = GVarName( "DEBUG_LOADING" );
    MakeReadWriteGVar(var);
    AssGVar( var, (SyDebugLoading ? True : False) );
    MakeReadOnlyGVar(var);


    ViewObjGVar = GVarName( "ViewObj" );
    CustomViewGVar = GVarName( "CustomView" );


    Last              = GVarName( "last"  );
    Last2             = GVarName( "last2" );
    Last3             = GVarName( "last3" );
    Time              = GVarName( "time"  );
    SaveOnExitFileGVar= GVarName( "SaveOnExitFile" );
    QUITTINGGVar      = GVarName( "QUITTING" );


    return 0;
}
