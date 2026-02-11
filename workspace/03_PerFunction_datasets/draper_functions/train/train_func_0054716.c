free_external_acl(void *data)
{
    external_acl *p = data;
    safe_free(p->name);
    while (p->format) {
	external_acl_format *f = p->format;
	p->format = f->next;
	cbdataFree(f);
    }
    wordlistDestroy(&p->cmdline);
    if (p->helper) {
	helperShutdown(p->helper);
	helperFree(p->helper);
	p->helper = NULL;
    }
    while (p->lru_list.tail)
	external_acl_cache_delete(p, p->lru_list.tail->data);
    if (p->cache)
	hashFreeMemory(p->cache);
}
