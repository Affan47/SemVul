_cache_find_page(struct gcide_idx_file *file, size_t n)
{
    size_t i;

    for (i = 0; i < file->cache_used; i++) {
	if (file->cache[i]->pageno == n) {
	    struct gcide_idx_cache *cp = file->cache[i];
	    _cache_promote(file, n);
	    return cp;
	}
    }

    return NULL;
}
