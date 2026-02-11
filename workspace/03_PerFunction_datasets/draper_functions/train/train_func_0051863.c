evas_common_scale_rgba_mipmap_down_2x2_mmx(DATA32 *src, DATA32 *dst, int src_w, int src_h)
{
   int x, y, dst_w, dst_h;
   DATA32 *src_ptr, *src_ptr2, *dst_ptr;

   dst_w = src_w >> 1;
   dst_h = src_h >> 1;

   if (dst_w < 1) dst_w = 1;
   if (dst_h < 1) dst_h = 1;


   dst_ptr = dst;
   for (y = 0; y < dst_h; y++)
     {
	src_ptr = src + (y * src_w * 2);
	src_ptr2 = src_ptr + src_w;
	for (x = 0; x < dst_w; x++)
	  {
	     punpcklbw_m2r(src_ptr[0], mm0);
	     punpcklbw_m2r(src_ptr[1], mm1);
	     punpcklbw_m2r(src_ptr2[0], mm2);
	     punpcklbw_m2r(src_ptr2[1], mm3);
	     psrlw_i2r(8, mm0);
	     psrlw_i2r(8, mm1);
	     psrlw_i2r(8, mm2);
	     psrlw_i2r(8, mm3);
	     paddw_r2r(mm1, mm0);
	     paddw_r2r(mm2, mm0);
	     paddw_r2r(mm3, mm0);
	     psrlw_i2r(2, mm0);
	     packuswb_r2r(mm0, mm0);
	     movd_r2m(mm0, dst_ptr[0]);

	     src_ptr+=2;
	     src_ptr2+=2;
	     dst_ptr++;
	  }
     }
}
