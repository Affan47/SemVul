cache_lookup_hash(unsigned char *md5, size_t len, struct CACHE *cache, uint32_t reclevel) {
    unsigned int key = getkey(md5);
    int ret = CL_VIRUS;
    struct CACHE *c;

    c = &cache[key];
    if(pthread_mutex_lock(&c->mutex)) {
	cli_errmsg("cache_lookup_hash: cache_lookup_hash: mutex lock fail\n");
	return ret;
    }


    ret = (cacheset_lookup(&c->cacheset, md5, len, reclevel)) ? CL_CLEAN : CL_VIRUS;
    pthread_mutex_unlock(&c->mutex);

    return ret;
}
