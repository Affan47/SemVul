alloc_clear(size)
    unsigned	    size;
{
    char_u *p;

    p = lalloc((long_u)size, TRUE);
    if (p != NULL)
	(void)vim_memset(p, 0, (size_t)size);
    return p;
}
