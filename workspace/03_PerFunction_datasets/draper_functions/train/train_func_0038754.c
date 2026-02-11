drmSLNext(void *l, unsigned long *key, void **value)
{
    SkipListPtr   list = (SkipListPtr)l;
    SLEntryPtr    entry;

    if (list->magic != SL_LIST_MAGIC) return -1;

    entry    = list->p0;

    if (entry) {
	list->p0 = entry->forward[0];
	*key     = entry->key;
	*value   = entry->value;
	return 1;
    }
    list->p0 = NULL;
    return 0;
}
