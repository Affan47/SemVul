evas_common_convert_rgba_to_16bpp_bgr_565_dith (DATA32 *src, DATA8 *dst, int src_jump, int dst_jump, int w, int h, int dith_x, int dith_y, DATA8 *pal)
{
   DATA32 *src_ptr;
   DATA16 *dst_ptr;
   int x, y;
   DATA8 r, g, b;
#ifndef BUILD_NO_DITHER_MASK
   DATA8 dith, dith2;
#endif

   dst_ptr = (DATA16 *)dst;

   CONVERT_LOOP_START_ROT_0();

   r = (R_VAL(src_ptr)) >> 3;
   g = (G_VAL(src_ptr)) >> 2;
   b = (B_VAL(src_ptr)) >> 3;

#ifndef BUILD_NO_DITHER_MASK
   dith = DM_TABLE[(x + dith_x) & DM_MSK][(y + dith_y) & DM_MSK] >> DM_SHF(5);
   dith2 = DM_TABLE[(x + dith_x) & DM_MSK][(y + dith_y) & DM_MSK] >> DM_SHF(6);
   if (((R_VAL(src_ptr) - (r << 3)) >= dith ) && (r < 0x1f)) r++;
   if (((G_VAL(src_ptr) - (g << 2)) >= dith2) && (g < 0x3f)) g++;
   if (((B_VAL(src_ptr) - (b << 3)) >= dith ) && (b < 0x1f)) b++;
#endif

   *dst_ptr = (b << 11) | (g << 5) | (r);

   CONVERT_LOOP_END_ROT_0();
   return;
   (void)pal;
}
