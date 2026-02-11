get_default_rc_name()
{
    char *home;
    char *result;
#ifdef WIN32
    char *file = "ffe.rc";
#else
    char *file = ".fferc";
#endif

    result = NULL;
    home = getenv("HOME");
#ifdef WIN32
    if(home == NULL)
    {
        home = getenv("FFE_HOME");
        if(home == NULL)
        {
            home = getenv("USERPROFILE");
        }
    }
#endif
    if(home != NULL)
    {
            result = xmalloc(strlen(home) + strlen(file) + strlen(PATH_SEPARATOR_STRING) + 2);
            strcpy(result,home);
            strcat(result,PATH_SEPARATOR_STRING);
            strcat(result,file);
    } else
    {
        result = file;
    }
    return result;
}
