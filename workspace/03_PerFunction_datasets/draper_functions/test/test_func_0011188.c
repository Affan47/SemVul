spool_getheader(hdrcache_t cache, const char *phead)
{
    char *head;
    const char **ret = NULL;
    int clinit, cl;

    assert(cache && phead);

    head = xstrdup(phead);
    lcase(head);


    clinit = cl = hashheader(head);
    while (cache[cl] != NULL) {
	if (!strcmp(head, cache[cl]->name)) {
	    ret = (const char **) cache[cl]->contents;
	    break;
	}
	cl++;
	cl %= HEADERCACHESIZE;
	if (cl == clinit) break;
    }

    free(head);

    return ret;
}
