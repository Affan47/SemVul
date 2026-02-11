free_tags(void)
{
    register int i;

    if (tag_table == 0) return;

    for (i = 0; i < ntags; ++i)
    {
        assert(tag_table[i]);
        FREE(tag_table[i]);
    }
    FREE(tag_table);
}
