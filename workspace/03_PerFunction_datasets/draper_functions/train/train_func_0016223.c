add_data_to_buffer(struct prof_buf *b, const void *d, size_t len)
{
    if (b->err)
        return;
    if (b->max - b->cur < len) {
        size_t newsize;
        char *newptr;

        newsize = b->max + (b->max >> 1) + len + 1024;
        newptr = realloc(b->base, newsize);
        if (newptr == NULL) {
            b->err = 1;
            return;
        }
        b->base = newptr;
        b->max = newsize;
    }
    memcpy(b->base + b->cur, d, len);
    b->cur += len;
}
