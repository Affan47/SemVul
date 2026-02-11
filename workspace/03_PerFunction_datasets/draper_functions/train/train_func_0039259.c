s_add_filter(stream **ps, const stream_template *templat,
             stream_state *ss, gs_memory_t *mem)
{
    stream *es;
    stream_state *ess;
    uint bsize = max(templat->min_in_size, 256);
    byte *buf;


    if (bsize > (*ps)->bsize && templat->process != s_NullE_template.process) {
        stream_template null_template;

        null_template = s_NullE_template;
        null_template.min_in_size = bsize;
        if (s_add_filter(ps, &null_template, NULL, mem) == 0)
            return 0;
    }
    es = s_alloc(mem, "s_add_filter(stream)");
    buf = gs_alloc_bytes(mem, bsize, "s_add_filter(buf)");
    if (es == 0 || buf == 0) {
        gs_free_object(mem, buf, "s_add_filter(buf)");
        gs_free_object(mem, es, "s_add_filter(stream)");
        return 0;
    }
    ess = (ss == 0 ? (stream_state *)es : ss);
    ess->templat = templat;
    ess->memory = mem;
    es->memory = mem;
    if (s_init_filter(es, ess, buf, bsize, *ps) < 0)
        return 0;
    *ps = es;
    return es;
}
