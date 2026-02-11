cpu_info_strval(char *ptr)
{
    if ((ptr = strchr(ptr, ':'))) {
        ptr++;
        while (isspace (*ptr)) ptr++;
        return ptr;
    }
    return NULL;
}
