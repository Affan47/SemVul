eet_jpeg_membuf_dst(j_compress_ptr cinfo,
                    void         **buf,
                    size_t        *len)
{
   struct jpeg_membuf_dst *dst;

   dst = calloc(1, sizeof(*dst));
   if (!dst)
     return -1;

   dst->buf = malloc(32768);
   if (!dst->buf)
     {
        free(dst);
        return -1;
     }

   dst->self = dst;
   dst->len = 32768;

   cinfo->dest = &dst->pub;
   dst->pub.init_destination = _eet_jpeg_membuf_dst_init;
   dst->pub.empty_output_buffer = _eet_jpeg_membuf_dst_flush;
   dst->pub.term_destination = _eet_jpeg_membuf_dst_term;
   dst->pub.free_in_buffer = dst->len;
   dst->pub.next_output_byte = dst->buf;
   dst->dst_buf = buf;
   dst->dst_len = len;
   dst->failed = 0;

   return 0;
}
