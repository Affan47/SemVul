mxf_write_klv_fill(AVFormatContext *s)
{
    unsigned pad = klv_fill_size(url_ftell(s->pb));
    if (pad) {
        put_buffer(s->pb, klv_fill_key, 16);
        pad -= 16 + 4;
        klv_encode_ber4_length(s->pb, pad);
        for (; pad; pad--)
            put_byte(s->pb, 0);
        assert(!(url_ftell(s->pb) & (KAG_SIZE-1)));
    }
}
