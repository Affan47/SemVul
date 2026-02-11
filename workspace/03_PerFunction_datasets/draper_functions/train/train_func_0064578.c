evas_common_scale_rgb_mipmap_down_2x2_c(DATA32 *src, DATA32 *dst, int src_w, int src_h)
{
   int x, y, dst_w, dst_h;
   DATA32 *src_ptr, *src_ptr2, *dst_ptr;

   dst_w = src_w >> 1;
   dst_h = src_h >> 1;

   if (dst_w < 1) dst_w = 1;
   if (dst_h < 1) dst_h = 1;

   src_ptr = src;
   src_ptr2 = src + src_w;
   dst_ptr = dst;
   for (y = 0; y < dst_h; y++)
     {
	for (x = 0; x < dst_w; x++)
	  {
	     R_VAL(dst_ptr) = (R_VAL(src_ptr) + R_VAL(src_ptr + 1) + R_VAL(src_ptr2) + R_VAL(src_ptr2 + 1)) >> 2;
	     G_VAL(dst_ptr) = (G_VAL(src_ptr) + G_VAL(src_ptr + 1) + G_VAL(src_ptr2) + G_VAL(src_ptr2 + 1)) >> 2;
	     B_VAL(dst_ptr) = (B_VAL(src_ptr) + B_VAL(src_ptr + 1) + B_VAL(src_ptr2) + B_VAL(src_ptr2 + 1)) >> 2;
	     A_VAL(dst_ptr) = 0xff;

	     src_ptr+=2;
	     src_ptr2+=2;
	     dst_ptr++;
	  }
	src_ptr += src_w;
	src_ptr2 += src_w;
     }
}
