GetAttributeValue(void* attr, const char* pszAttributeName)
{
    const char** papszIter = (const char** )attr;
    while(*papszIter)
    {
        if (strcmp(*papszIter, pszAttributeName) == 0)
        {
            return CPLStrdup(papszIter[1]);
        }
        papszIter += 2;
    }
    return NULL;
}
