upd_rgb_3color(gx_device *pdev, const gx_color_value cv[])
{
   const upd_p     upd = ((upd_device *)pdev)->upd;
   gx_color_index  rv;
   gx_color_value r, g, b;
   r = cv[0]; g = cv[1]; b = cv[2];

   rv = upd_truncate(upd,0,r) | upd_truncate(upd,1,g) | upd_truncate(upd,2,b);
   if(rv == gx_no_color_index) rv ^= 1;

#if UPD_MESSAGES & UPD_M_MAPCALLS
  errprintf(pdev->memory,
   "rgb_3color: (%5.1f,%5.1f,%5.1f) : (%5.1f,%5.1f,%5.1f) : 0x%0*lx\n",
   255.0 * (double) r / (double) gx_max_color_value,
   255.0 * (double) g / (double) gx_max_color_value,
   255.0 * (double) b / (double) gx_max_color_value,
   255.0 * (double) ((rv >> upd->cmap[0].bitshf) & upd->cmap[0].bitmsk)
                 / (double) upd->cmap[0].bitmsk,
   255.0 * (double) ((rv >> upd->cmap[1].bitshf) & upd->cmap[1].bitmsk)
                 / (double) upd->cmap[1].bitmsk,
   255.0 * (double) ((rv >> upd->cmap[2].bitshf) & upd->cmap[2].bitmsk)
                 / (double) upd->cmap[2].bitmsk,
   (pdev->color_info.depth + 3)>>2,rv);
#endif

   return rv;
}
