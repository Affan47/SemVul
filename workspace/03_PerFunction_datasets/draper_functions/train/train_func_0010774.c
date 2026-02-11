bufport_fill(ScmPort *p, int min, int allow_less)
{
    int cursiz = (int)(p->src.buf.end - p->src.buf.current);
    int nread = 0, toread;
    if (cursiz > 0) {
        memmove(p->src.buf.buffer, p->src.buf.current, cursiz);
        p->src.buf.current = p->src.buf.buffer;
        p->src.buf.end = p->src.buf.current + cursiz;
    } else {
        p->src.buf.current = p->src.buf.end = p->src.buf.buffer;
    }
    if (min <= 0) min = SCM_PORT_BUFFER_ROOM(p);
    if (p->src.buf.mode != SCM_PORT_BUFFER_NONE) {
        toread = SCM_PORT_BUFFER_ROOM(p);
    } else {
        toread = min;
    }

    do {
        int r = p->src.buf.filler(p, toread-nread);
        if (r <= 0) break;
        nread += r;
        p->src.buf.end += r;
    } while (!allow_less && nread < min);
    return nread;
}
