stringLength(const char  *src,
             size_t       size)
{
l_int32  i;

    PROCNAME("stringLength");

    if (!src)
        return ERROR_INT("src not defined", procName, 0);
    if (size < 1)
        return 0;

    for (i = 0; i < size; i++) {
        if (src[i] == '\0')
            return i;
    }
    return size;
}
