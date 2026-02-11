join_path2(const char *p1, size_t n1, const char *p2, size_t n2)
{
    char *ret, *p;

    if (!p1 || !p2)
        return NULL;

    if (!n1)
        n1 = strlen(p1);
    if (!n2)
        n2 = strlen(p2);

    ret = malloc(n1 + n2 + 2);
    if (!ret)
        return NULL;

    memcpy(ret, p1, n1+1);

    p = ret + n1 - 1;


    if (*p != '/')
        *(++p) = '/';


    if (*p2 == '/')
    {
        p2++;
        n2--;
    }

    memcpy(++p, p2, n2+1);
    return ret;
}
