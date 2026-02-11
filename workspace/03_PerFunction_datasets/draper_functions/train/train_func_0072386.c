OGROSMFormatForHSTORE(const char* pszV, char* pszAllTags)
{
    int k;

    int nAllTagsOff = 0;

    pszAllTags[nAllTagsOff++] = '"';

    for(k=0;pszV[k] != '\0'; k++)
    {
        if( pszV[k] == '"' || pszV[k] == '\\' )
            pszAllTags[nAllTagsOff++] = '\\';
        pszAllTags[nAllTagsOff++] = pszV[k];
    }

    pszAllTags[nAllTagsOff++] = '"';

    return nAllTagsOff;
}
