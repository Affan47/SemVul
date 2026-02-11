hash(const char *name)
{
    const char *s;
    unsigned h;

    h = 0;
    s = name;
    while (*s != '\0')
	h = (h << 1) ^ (unsigned char) (*s++);
    return h % SYM_MAX_HASH;
}
