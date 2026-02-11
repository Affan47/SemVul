BuildFullQueryStatement()

{
    if( pszQueryStatement != NULL )
    {
        CPLFree( pszQueryStatement );
        pszQueryStatement = NULL;
    }

    pszQueryStatement = (char*) CPLMalloc(strlen(pszRawStatement) + strlen(osWHERE) + 40);

    if (strlen(osWHERE) == 0)
        strcpy(pszQueryStatement, pszRawStatement);
    else
        sprintf(pszQueryStatement, "SELECT * FROM (%s) AS ogrpgsubquery %s",
                pszRawStatement, osWHERE.c_str());
}
