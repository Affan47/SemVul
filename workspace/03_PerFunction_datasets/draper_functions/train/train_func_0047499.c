xmalloc(size_t n)
{
        void *p = malloc(n ? n : 1);
        if (!p)
                fatal(0, "out of memory");
        return p;
}
