tdx_index_open(bool writable)
{
    struct group_index *index;
    struct stat st;

    index = xmalloc(sizeof(struct group_index));
    index->path = concatpath(innconf->pathoverview, "group.index");
    index->writable = writable;
    if (!file_open_group_index(index, &st)) {
	goto fail;
    }
    if ((size_t) st.st_size > sizeof(struct group_header)) {
        index->count = index_entry_count(st.st_size);
        if (!index_map(index))
            goto fail;
    } else {
        index->count = 0;
        if (index->writable) {
            if (st.st_size > 0)
                warn("tradindexed: recreating truncated %s", index->path);
            if (!index_expand(index))
                goto fail;
        } else {
            index->header = NULL;
            index->entries = NULL;
        }
    }
    return index;

 fail:
    tdx_index_close(index);
    return NULL;
}
