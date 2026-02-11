ReadDir( const char *pszPath )

{
    CPLMutexHolder oHolder( &hMutex );

    CPLString osPath = pszPath;

    NormalizePath( osPath );

    std::map<CPLString,VSIMemFile*>::const_iterator iter;
    char **papszDir = NULL;
    int nPathLen = strlen(osPath);

    if( osPath[nPathLen-1] == '/' )
        nPathLen--;


    int nItems=0;
    int nAllocatedItems=0;

    for( iter = oFileList.begin(); iter != oFileList.end(); ++iter )
    {
        const char *pszFilePath = iter->second->osFilename.c_str();
        if( EQUALN(osPath,pszFilePath,nPathLen)
            && pszFilePath[nPathLen] == '/'
            && strstr(pszFilePath+nPathLen+1,"/") == NULL )
        {
            if (nItems == 0)
            {
                papszDir = (char**) CPLCalloc(2,sizeof(char*));
                nAllocatedItems = 1;
            }
            else if (nItems >= nAllocatedItems)
            {
                nAllocatedItems = nAllocatedItems * 2;
                papszDir = (char**)CPLRealloc(papszDir,
                                              (nAllocatedItems+2)*sizeof(char*));
            }

            papszDir[nItems] = CPLStrdup(pszFilePath+nPathLen+1);
            papszDir[nItems+1] = NULL;

            nItems++;
        }
    }

    return papszDir;
}
