item_alloc2(size_t ntotal) {
    item *it;
    if (ntotal > settings.item_buf_size){
        it = (item *)malloc(ntotal);
        if (it == NULL){
            return NULL;
        }
        memset(it, 0, ntotal);
        if (settings.verbose > 1) {
            fprintf(stderr, "alloc a item buffer from malloc.\n");
        }
    }else{
        it = item_from_freelist();
        if (it == NULL){
            return NULL;
        }
        if (settings.verbose > 1) {
            fprintf(stderr, "alloc a item buffer from freelist.\n");
        }
    }

    return it;
}
