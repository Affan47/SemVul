ios_skip(ios_t *s, off_t offs)
{
    if (offs != 0) {
        if (offs > 0) {
            if (offs <= (off_t)(s->size-s->bpos)) {
                s->bpos += offs;
                return 0;
            }
            else if (s->bm == bm_mem) {

                return -1;
            }
        }
        else if (offs < 0) {
            if (-offs <= (off_t)s->bpos) {
                s->bpos += offs;
                s->_eof = 0;
                return 0;
            }
            else if (s->bm == bm_mem) {
                return -1;
            }
        }
        ios_flush(s);
        if (s->state == bst_wr)
            offs += s->bpos;
        else if (s->state == bst_rd)
            offs -= (s->size - s->bpos);
        off_t fdpos = lseek(s->fd, offs, SEEK_CUR);
        if (fdpos == (off_t)-1)
            return fdpos;
        s->fpos = fdpos;
        s->bpos = s->size = 0;
        s->_eof = 0;
    }
    return 0;
}
