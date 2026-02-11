is_refill(InStream *is)
{
    off_t start = is->buf.start + is->buf.pos;
    off_t last = start + BUFFER_SIZE;
    off_t flen = is->m->length_i(is);

    if (last > flen) {
        last = flen;
    }

    is->buf.len = last - start;
    if (is->buf.len <= 0) {
        RAISE(EOF_ERROR, "current pos = %"F_OFF_T_PFX"d, "
              "file length = %"F_OFF_T_PFX"d", start, flen);
    }

    is->m->read_i(is, is->buf.buf, is->buf.len);

    is->buf.start = start;
    is->buf.pos = 0;
}
