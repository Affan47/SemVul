memcpy (void *dest, const void *src, unsigned int len)
{
    const char *sp = (const char *)src;
    char *dp = (char *)dest;
    for(; len != 0; len--) *dp++ = *sp++;
}
