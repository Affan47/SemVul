lookup_table4_nth(const struct gen_table4 *tbl, const char *search_str)
{
    int k = -1;
    while (tbl[++k].key)
	if (tbl[k].key && !strncmp(search_str, tbl[k].key, strlen(tbl[k].key)))
	    return k;
    return -1;
}
