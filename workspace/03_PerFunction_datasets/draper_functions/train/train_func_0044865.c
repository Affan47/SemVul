u_astrnlen(const char *s1, int32_t n)
{
    int32_t len = 0;

    if (s1)
    {
        while (n-- && *(s1++))
        {
            len++;
        }
    }
    return len;
}
