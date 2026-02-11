sfnts_writer_wword(sfnts_writer *w, ushort v)
{
    if (w->buf + w->buf_size < w->p + 2)
        return;
    w->p[0] = v / 256;
    w->p[1] = v % 256;
    w->p += 2;
}
