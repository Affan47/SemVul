ParseBandsFromURL( string oVarList )

{
    char **papszResultList = NULL;
    char **papszVars = CSLTokenizeString2( oVarList.c_str(), ",", 0 );
    int i;

    for( i = 0; papszVars != NULL && papszVars[i] != NULL; i++ )
    {
        string oVarName;
        string oCE;


        char *pszCEStart = strstr(papszVars[i],"[");


        if( pszCEStart == NULL )
        {
            oVarName = papszVars[i];

            papszResultList =
                CollectBandsFromDDSVar( oVarName, papszResultList );
        }
        else
        {
            oCE = pszCEStart;
            *pszCEStart = '\0';
            oVarName = papszVars[i];


            papszResultList = CSLAddString( papszResultList,
                                            oVarName.c_str() );
            papszResultList = CSLAddString( papszResultList,
                                            oCE.c_str() );
        }
    }

    CSLDestroy(papszVars);

    return papszResultList;
}
