ios_close(ios_t *s)
{
    ios_flush(s);
    if (s->fd != -1 && s->ownfd)
        close(s->fd);
    s->fd = -1;
    if (s->buf!=NULL && s->ownbuf && s->buf!=&s->local[0]) {
        LLT_FREE(s->buf);
    }
    s->buf = NULL;
    s->size = s->maxsize = s->bpos = 0;
}
