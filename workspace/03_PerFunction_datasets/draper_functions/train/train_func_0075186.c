GetFeatureClass( int iFCIndex,
                                       char ** ppszFCId,
                                       char ** ppszFCName )

{
    if( iFCIndex < 0 || iFCIndex >= nFCCount )
    {
        *ppszFCId = NULL;
        *ppszFCName = NULL;
        return FALSE;
    }
    else
    {
        *ppszFCId = papszFCNum[iFCIndex];
        *ppszFCName = papszFCName[iFCIndex];
        return TRUE;
    }
}
