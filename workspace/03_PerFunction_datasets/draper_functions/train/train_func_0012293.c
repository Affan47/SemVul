_cache_alloc(struct gcide_idx_file *file)
{
    struct gcide_idx_cache *cp;

    if (!file->cache) {
	file->cache = calloc(file->cache_size, sizeof(file->cache[0]));
	if (!file->cache) {
	    dico_log(L_ERR, ENOMEM, "gcide _cache_alloc");
	    return NULL;
	}
    }
    if (file->cache_used < file->cache_size) {
	if (file->cache_used &&
	    file->cache[file->cache_used - 1]->refcount == 0)
	    return file->cache[file->cache_used - 1];
	cp = calloc(1, sizeof(*cp));
	if (!cp) {
	    dico_log(L_ERR, ENOMEM, "gcide _cache_alloc");
	    return NULL;
	}
	cp->page = malloc(file->header.ihdr_pagesize);
	if (!cp->page) {
	    dico_log(L_ERR, ENOMEM, "gcide _cache_alloc");
	    free(cp);
	    return NULL;
	}
	file->cache[file->cache_used++] = cp;
    } else
	cp = file->cache[file->cache_used - 1];
    cp->pageno = 0;
    cp->refcount = 0;
    return cp;
}
