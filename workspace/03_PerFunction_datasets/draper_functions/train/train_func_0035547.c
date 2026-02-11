rfind(const char *cs, char *str, size_t len)
{
    if(!len)
        len = strlen(str);

    while(len--) {
        if(strchr(cs, str[len]))
            return str + len;
    }
    return str;
}
