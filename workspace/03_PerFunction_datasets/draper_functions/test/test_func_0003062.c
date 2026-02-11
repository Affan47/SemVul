_eet_jpeg_membuf_dst_term(j_compress_ptr cinfo)
{
   struct jpeg_membuf_dst *dst = ((struct jpeg_membuf_dst *)cinfo->dest)->self;

   if (dst->failed)
     {
        *dst->dst_buf = NULL;
        *dst->dst_len = 0;
        free(dst->buf);
     }
   else
     {
        *dst->dst_buf = dst->buf;
        *dst->dst_len = (unsigned char *)dst->pub.next_output_byte - dst->buf;
     }

   free(dst);
   cinfo->dest = NULL;
}
