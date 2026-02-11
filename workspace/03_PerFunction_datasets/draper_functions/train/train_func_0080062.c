XP_GetStringFromDatabase(char* strLibraryName,
                         char* strLanguage,
                         int key)
{
    char *result = NULL;


    if (result == NULL)
        result = XP_GetStringFromMemory(strLibraryName,key);
    return result;
}
