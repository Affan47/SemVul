deflateTune(z_streamp strm, int good_length, int max_lazy, int nice_length, int max_chain)
{
   deflate_state *s;

   if (strm == Z_NULL || strm->state == Z_NULL) return Z_STREAM_ERROR;
   s = (deflate_state*)strm->state;
   s->good_match = good_length;
   s->max_lazy_match = max_lazy;
   s->nice_match = nice_length;
   s->max_chain_length = max_chain;
   return Z_OK;
}
