_tr_align(deflate_state *s)
{
   send_bits(s, STATIC_TREES<<1, 3);
   send_code(s, END_BLOCK, static_ltree);
#ifdef DEBUG
   s->compressed_len += 10L;
#endif
   bi_flush(s);
}
