_tr_stored_block(s, buf, stored_len, last)
    deflate_state *s;
    charf *buf;
    ulg stored_len;
    int last;
{
    send_bits(s, (STORED_BLOCK<<1)+last, 3);
#ifdef DEBUG
    s->compressed_len = (s->compressed_len + 3 + 7) & (ulg)~7L;
    s->compressed_len += (stored_len + 4) << 3;
#endif
    copy_block(s, buf, (unsigned)stored_len, 1);
}
