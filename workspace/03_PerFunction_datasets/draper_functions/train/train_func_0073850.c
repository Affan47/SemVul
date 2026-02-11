ios_write(ios_t *s, char *data, size_t n)
{
    if (s->readonly) return 0;
    if (n == 0) return 0;
    size_t space;
    size_t wrote = 0;

    if (s->state == bst_none) s->state = bst_wr;
    if (s->state == bst_rd) {
        if (!s->rereadable) {
            s->size = 0;
            s->bpos = 0;
        }
        space = s->size - s->bpos;
    }
    else {
        space = s->maxsize - s->bpos;
    }

    if (s->bm == bm_mem) {
        wrote = _write_grow(s, data, n);
    }
    else if (s->bm == bm_none) {
        s->fpos = -1;
        _os_write_all(s->fd, data, n, &wrote);
        return wrote;
    }
    else if (n <= space) {
        if (s->bm == bm_line) {
            char *nl;
            if ((nl=(char*)memrchr(data, '\n', n)) != NULL) {
                size_t linesz = nl-data+1;
                s->bm = bm_block;
                wrote += ios_write(s, data, linesz);
                ios_flush(s);
                s->bm = bm_line;
                n -= linesz;
                data += linesz;
            }
        }
        memcpy(s->buf + s->bpos, data, n);
        s->bpos += n;
        wrote += n;
    }
    else {
        s->state = bst_wr;
        ios_flush(s);
        if (n > MOST_OF(s->maxsize)) {
            _os_write_all(s->fd, data, n, &wrote);
            return wrote;
        }
        return ios_write(s, data, n);
    }
    _write_update_pos(s);
    return wrote;
}
