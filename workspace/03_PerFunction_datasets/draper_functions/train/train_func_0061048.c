zmalloc(size_t size) {
    void *ptr = malloc(size+sizeof(size_t));

    if (!ptr) return NULL;
    *((size_t*)ptr) = size;
    used_memory += size+sizeof(size_t);
#ifdef DEBUG
	mallocd += size+sizeof(size_t);
#endif
    return (char*)ptr+sizeof(size_t);
}
