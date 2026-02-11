s_MD5C_make_stream(gs_memory_t *mem, stream *strm)
{
    stream *s = s_alloc(mem, "s_MD5E_make_stream");
    stream_state *ss = s_alloc_state(mem, s_MD5E_template.stype, "s_MD5E_make_stream");
    int buffer_size = 1024;
    byte *buffer = gs_alloc_bytes(mem, buffer_size, "s_MD5E_make_stream(buffer)");

    if (ss == NULL || s == NULL || buffer == NULL)
        goto err;
    ss->templat = &s_MD5C_template;
    if (s_init_filter(s, ss, buffer, buffer_size, NULL) < 0)
        goto err;
    s->strm = strm;
    s->close_strm = true;
    return s;
err:
    gs_free_object(mem, ss, "s_MD5E_make_stream");
    gs_free_object(mem, s, "s_MD5E_make_stream");
    gs_free_object(mem, buffer, "s_MD5E_make_stream");
    return NULL;
}
