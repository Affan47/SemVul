dfb_fbdev_set_gamma_ramp( DFBSurfacePixelFormat format )
{
     int i;

     int red_size   = 0;
     int green_size = 0;
     int blue_size  = 0;
     int red_max    = 0;
     int green_max  = 0;
     int blue_max   = 0;

     struct fb_cmap *cmap;

     if (!dfb_fbdev) {
          D_BUG( "dfb_fbdev_set_gamma_ramp() called while dfb_fbdev == NULL!" );

          return DFB_BUG;
     }

     switch (format) {
          case DSPF_ARGB1555:
          case DSPF_RGB555:
	   case DSPF_BGR555:
               red_size   = 32;
               green_size = 32;
               blue_size  = 32;
               break;
          case DSPF_ARGB4444:
          case DSPF_RGB444:
               red_size   = 16;
               green_size = 16;
               blue_size  = 16;
               break;
          case DSPF_RGB16:
               red_size   = 32;
               green_size = 64;
               blue_size  = 32;
               break;
          case DSPF_RGB24:
          case DSPF_RGB32:
          case DSPF_ARGB:
               red_size   = 256;
               green_size = 256;
               blue_size  = 256;
               break;
          default:
               return DFB_OK;
     }


     if (dfb_fbdev->shared->fix.visual == FB_VISUAL_DIRECTCOLOR) {
          red_max   = 65536 / (256/red_size);
          green_max = 65536 / (256/green_size);
          blue_max  = 65536 / (256/blue_size);
     }
     else {
          red_max   = red_size;
          green_max = green_size;
          blue_max  = blue_size;
     }

     cmap = &dfb_fbdev->shared->current_cmap;


     cmap->len = green_size;

     for (i = 0; i < red_size; i++)
          cmap->red[i] = dfb_fbdev_calc_gamma( i, red_max );

     for (i = 0; i < green_size; i++)
          cmap->green[i] = dfb_fbdev_calc_gamma( i, green_max );

     for (i = 0; i < blue_size; i++)
          cmap->blue[i] = dfb_fbdev_calc_gamma( i, blue_max );


     if (dfb_fbdev->shared->fix.visual == FB_VISUAL_DIRECTCOLOR) {
          for (i = 0; i < red_size; i++)
               cmap->red[i] |= cmap->red[i] << 8;

          for (i = 0; i < green_size; i++)
               cmap->green[i] |= cmap->green[i] << 8;

          for (i = 0; i < blue_size; i++)
               cmap->blue[i] |= cmap->blue[i] << 8;
     }

     if (FBDEV_IOCTL( FBIOPUTCMAP, cmap ) < 0) {
          D_PERROR( "DirectFB/FBDev: "
                     "Could not set gamma ramp" );

          return errno2result(errno);
     }

     return DFB_OK;
}
