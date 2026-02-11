composeCompoundCommand(char * ptr_prev, size_t len_prev,
                              char ** pptr, size_t * plen) {
    char * ptr;
    size_t len;
    size_t i;


    if (pptr == NULL || plen == NULL)
        return FALSE;


    if (ptr_prev == NULL || len_prev == 0)
        return TRUE;

    ptr = *pptr;
    len = *plen;


    if (len == 0 || ptr == NULL)
        return FALSE;


    if (ptr[0] == '*' || ptr[0] == ':')
        return TRUE;


    if (ptr_prev[0] == '*')
        return TRUE;


    for (i = len_prev; i > 0; i--) {
        if (ptr_prev[i-1] == ':') {
            break;
        }
    }


    if (i == 0)
        return TRUE;

    ptr -= i;
    len += i;
    memmove(ptr, ptr_prev, i);
    *plen = len;
    *pptr = ptr;
    return TRUE;
}
