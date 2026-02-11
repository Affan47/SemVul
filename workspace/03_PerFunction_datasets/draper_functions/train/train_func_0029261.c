s_alloc_position_stream(stream ** ps, gs_memory_t * mem)
{
    stream *s = *ps = s_alloc(mem, "s_alloc_position_stream");

    if (s == 0)
        return_error(gs_error_VMerror);
    swrite_position_only(s);
    return 0;
}
