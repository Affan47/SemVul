wma_window(WMADecodeContext *s, fixed32 *in, fixed32 *out)
 {

     int block_len, bsize, n;


     if (s->block_len_bits <= s->prev_block_len_bits) {
         block_len = s->block_len;
         bsize = s->frame_len_bits - s->block_len_bits;

         vector_fmul_add_add(out, in, s->windows[bsize], block_len);

     } else {

         block_len = 1 << s->prev_block_len_bits;

         n = (s->block_len - block_len) / 2;
         bsize = s->frame_len_bits - s->prev_block_len_bits;

         vector_fmul_add_add(out+n, in+n, s->windows[bsize],  block_len);

         memcpy(out+n+block_len, in+n+block_len, n*sizeof(fixed32));
     }


     out += s->block_len;
     in += s->block_len;


     if (s->block_len_bits <= s->next_block_len_bits) {
         block_len = s->block_len;
         bsize = s->frame_len_bits - s->block_len_bits;

         vector_fmul_reverse(out, in, s->windows[bsize], block_len);

     } else {
         block_len = 1 << s->next_block_len_bits;
         n = (s->block_len - block_len) / 2;
         bsize = s->frame_len_bits - s->next_block_len_bits;

         memcpy(out, in, n*sizeof(fixed32));

         vector_fmul_reverse(out+n, in+n, s->windows[bsize], block_len);

         memset(out+n+block_len, 0, n*sizeof(fixed32));
     }
 }
