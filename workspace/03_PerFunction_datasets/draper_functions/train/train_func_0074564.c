s_process_read_buf(stream * s)
{
    int status;

    stream_compact(s, false);
    status = sreadbuf(s, &s->cursor.w);
    s->end_status = (status >= 0 ? 0 : status);
    return 0;
}
