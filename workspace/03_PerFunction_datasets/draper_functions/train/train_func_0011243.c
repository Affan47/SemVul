M_GetFilePath(const char *fn, char *dest, size_t len)
{
    boolean found_slash = false;
    char *p;
    char sepchar = '\0';

    memset(dest, 0, len);

    p = dest + len - 1;

    strncpy(dest, fn, len);

    while(p >= dest)
    {
        if(*p == '/' || *p == '\\')
        {
            sepchar = *p;
            found_slash = true;
            *p = '\0';
            break;
        }
        *p = '\0';
        p--;
    }


    if(!found_slash && *dest == '\0')
        *dest = '.';


    if(sepchar == '\0')
        sepchar = '/';

    return sepchar;
}
