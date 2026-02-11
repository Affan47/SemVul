strGetBoolean(const char * str)
{
    static const char * sTrue[] =
    {
        "true", "yes", "on", "1", "ja", "si", "oui", NULL
    };
    static const char * sFalse[] =
    {
        "false", "no", "off", "0", NULL
    };
    if(str[0] == 0)
    {
        return false;
    }

    bool matchedTrue = false;
    bool matchedFalse = false;

    const char ** next = sTrue;
    while(*next != NULL)
    {
        if(strIsCasePrefix(str, *next)  ||  strIsCasePrefix(*next, str))
        {
            matchedTrue = true;
        }
        next++;
    }
    next = sFalse;
    while(*next != NULL)
    {
        if(strIsCasePrefix(str, *next)  ||  strIsCasePrefix(*next, str))
        {
            matchedFalse = true;
        }
        next++;
    }
    if(matchedTrue  &&  !matchedFalse)
    {
        return true;
    }
    if(matchedFalse  &&  !matchedTrue)
    {
        return false;
    }


    return false;
}
