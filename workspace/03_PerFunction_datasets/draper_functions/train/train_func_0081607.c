ser_int_get(int *dest, int *source, const char *buf, int len)
{
    union
    {
        char c[sizeof(int)];
        int i;
    } u;
    int i;


    if(&(buf[*source]) + sizeof(int) > buf + (sizeof(char) * len))
        return 1;


    for(i = 0; i < sizeof(int); i++)
    {
        u.c[i] = buf[*source];
        (*source)++;
    }
    *dest = u.i;

    return 0;
}
