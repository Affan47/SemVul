s_zlibE_process(stream_state * st, stream_cursor_read * pr,
                stream_cursor_write * pw, bool last)
{
    stream_zlib_state *const ss = (stream_zlib_state *)st;
    z_stream *zs = &ss->dynamic->zstate;
    const byte *p = pr->ptr;
    int status;


    if (pw->ptr == pw->limit)
        return 1;
    if (p == pr->limit && !last)
        return 0;
    zs->next_in = (Bytef *)p + 1;
    zs->avail_in = pr->limit - p;
    zs->next_out = pw->ptr + 1;
    zs->avail_out = pw->limit - pw->ptr;
    status = deflate(zs, (last ? Z_FINISH : Z_NO_FLUSH));
    pr->ptr = zs->next_in - 1;
    pw->ptr = zs->next_out - 1;
    switch (status) {
        case Z_OK:
            return (pw->ptr == pw->limit ? 1 : pr->ptr > p && !last ? 0 : 1);
        case Z_STREAM_END:
            return (last && pr->ptr == pr->limit ? 0 : ERRC);
        default:
            return ERRC;
    }
}
