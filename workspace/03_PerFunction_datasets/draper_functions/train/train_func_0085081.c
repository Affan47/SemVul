upd_cmyk_kcolor(gx_device *pdev, const gx_color_value cv[])
{
   const upd_p     upd = ((upd_device *)pdev)->upd;
   gx_color_index  rv;
   gx_color_value  black;

   gx_color_value c, m, y, k;
   c = cv[0]; m = cv[1]; y = cv[2]; k = cv[3];

   if((c == m) && (m == y)) {

      black = c > k ? c : k;
      rv = upd_truncate(upd,0,black);

   } else {

      if(k && !(c | m | y)) {
         black = k;
      } else {
         black = c     < m ? c     : m;
         black = black < y ? black : y;
      }

      rv  = upd_truncate(upd,0,black) | upd_truncate(upd,1,c)
          | upd_truncate(upd,2,m)     | upd_truncate(upd,3,y);


      if(rv == gx_no_color_index) rv ^= 1;
   }

#if UPD_MESSAGES & UPD_M_MAPCALLS
  errprintf(pdev->memory,
"cmyk_kcolor: (%5.1f,%5.1f,%5.1f,%5.1f) : (%5.1f,%5.1f,%5.1f,%5.1f) : 0x%0*lx\n",
   255.0 * (double) c / (double) gx_max_color_value,
   255.0 * (double) m / (double) gx_max_color_value,
   255.0 * (double) y / (double) gx_max_color_value,
   255.0 * (double) k / (double) gx_max_color_value,
   255.0 * (double) ((rv >> upd->cmap[1].bitshf) & upd->cmap[1].bitmsk)
                 / (double) upd->cmap[1].bitmsk,
   255.0 * (double) ((rv >> upd->cmap[2].bitshf) & upd->cmap[2].bitmsk)
                 / (double) upd->cmap[2].bitmsk,
   255.0 * (double) ((rv >> upd->cmap[3].bitshf) & upd->cmap[3].bitmsk)
                 / (double) upd->cmap[3].bitmsk,
   255.0 * (double) ((rv >> upd->cmap[0].bitshf) & upd->cmap[0].bitmsk)
                 / (double) upd->cmap[0].bitmsk,
   (pdev->color_info.depth + 3)>>2,rv);
#endif

   return rv;
}
