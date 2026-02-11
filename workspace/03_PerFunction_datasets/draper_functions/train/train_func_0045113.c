fs_tlist_add(fs_tlist *l, fs_rid data[4])
{
    if (!l) {
        fs_error(LOG_CRIT, "tried to write to NULL list");
        return -1;
    }

    if (l->buffer_pos == LIST_BUFFER_SIZE) {
        int ret = fs_tlist_flush(l);
        if (ret != 0) return ret;
    }

    memcpy(l->buffer + l->buffer_pos * WIDTH, data, WIDTH);

    l->buffer_pos++;

    return l->offset + l->buffer_pos - 1;
}
