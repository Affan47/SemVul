basestr (const char *str)
{
        char *basestr = NULL;

        basestr = strrchr (str, '/');
        if (basestr)
                basestr ++;

        return basestr;
}
