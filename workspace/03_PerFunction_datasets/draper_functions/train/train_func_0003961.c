OGCWKTSetProj( char * pszProjection, char ** papszMethods,
                           const char * pszTransformName,
                           const char * pszParm1,
                           const char * pszParm2,
                           const char * pszParm3,
                           const char * pszParm4,
                           const char * pszParm5,
                           const char * pszParm6,
                           const char * pszParm7 )

{
    int		iParm, nCount = CSLCount(papszMethods);
    const char	*apszParmNames[8];

    apszParmNames[0] = pszParm1;
    apszParmNames[1] = pszParm2;
    apszParmNames[2] = pszParm3;
    apszParmNames[3] = pszParm4;
    apszParmNames[4] = pszParm5;
    apszParmNames[5] = pszParm6;
    apszParmNames[6] = pszParm7;
    apszParmNames[7] = NULL;

    sprintf( pszProjection,
             "PROJECTION[\"%s\"]",
             pszTransformName );

    for( iParm = 0; iParm < nCount-1 && apszParmNames[iParm] != NULL; iParm++ )
    {
        sprintf( pszProjection + strlen(pszProjection),
                 ",PARAMETER[\"%s\",%s]",
                 apszParmNames[iParm],
                 papszMethods[iParm+1] );
    }
}
