AddModule( const char *pszModule )

{
    if( CheckModule( pszModule ) )
        return;

    papszModules = CSLAddString( papszModules, pszModule );
    nModules++;
}
