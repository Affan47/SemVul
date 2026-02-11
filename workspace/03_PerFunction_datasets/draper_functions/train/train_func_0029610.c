s_RLE_init(stream_state * st)
{
    stream_RLE_state *const ss = (stream_RLE_state *) st;

    return s_RLE_init_inline(ss);
}
