cmap_put_ranges(stream *s, const gx_code_space_range_t *pcsr, int count)
{
    int i;

    pprintd1(s, "%d begincodespacerange\n", count);
    for (i = 0; i < count; ++i, ++pcsr) {
        stream_puts(s, "<");
        pput_hex(s, pcsr->first, pcsr->size);
        stream_puts(s, "><");
        pput_hex(s, pcsr->last, pcsr->size);
        stream_puts(s, ">\n");
    }
    stream_puts(s, "endcodespacerange\n");
}
