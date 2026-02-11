ImportFuncFromLibrary(
    const Char *        name,
    Obj *               address )
{
    if ( NrImportedFuncs == 1024 ) {
        Pr( "#W  warning: too many imported Funcs\n", 0L, 0L );
    }
    else {
        ImportedFuncs[NrImportedFuncs].name    = name;
        ImportedFuncs[NrImportedFuncs].address = address;
        NrImportedFuncs++;
    }
    if ( address != 0 ) {
        InitFopyGVar( name, address );
    }
}
