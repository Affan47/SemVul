pack_names(void)
{
    register bucket *bp;
    register char *p, *s, *t;

    name_pool_size = 13;
    for (bp = first_symbol; bp; bp = bp->next)
        name_pool_size += strlen(bp->name) + 1;
    name_pool = MALLOC(name_pool_size);
    if (name_pool == 0) no_space();

    strcpy(name_pool, "$accept");
    strcpy(name_pool+8, "$end");
    t = name_pool + 13;
    for (bp = first_symbol; bp; bp = bp->next)
    {
        p = t;
        s = bp->name;
        while ((*t++ = *s++)) continue;
        FREE(bp->name);
        bp->name = p;
    }
}
