r100_set_blitting_color( RadeonDriverData *rdrv,
                              RadeonDeviceData *rdev,
                              CardState        *state )
{
     DFBColor color   = state->color;
     u32      color3d;
     int      y, u, v;

     if (RADEON_IS_SET( COLOR ) && RADEON_IS_SET( BLITTING_FLAGS ))
          return;

     if (state->blittingflags & DSBLIT_COLORIZE &&
         state->blittingflags & DSBLIT_SRC_PREMULTCOLOR) {
          color.r = ((long) color.r * color.a / 255L);
          color.g = ((long) color.g * color.a / 255L);
          color.b = ((long) color.b * color.a / 255L);
     }

     switch (rdev->dst_format) {
          case DSPF_A8:
               color3d = (color.a << 24) | 0x00ffffff;
               break;
          case DSPF_I420:
          case DSPF_YV12:
               RGB_TO_YCBCR( color.r, color.g, color.b, y, u, v );
               rdev->y_cop  = PIXEL_ARGB( color.a, y, y, y );
               rdev->cb_cop = PIXEL_ARGB( color.a, u, u, u );
               rdev->cr_cop = PIXEL_ARGB( color.a, v, v, v );
               color3d = rdev->y_cop;
               break;
          case DSPF_AYUV:
               RGB_TO_YCBCR( color.r, color.g, color.b, y, u, v );
               color3d = PIXEL_AYUV( color.a, y, u, v );
               break;
          case DSPF_UYVY:
          case DSPF_YUY2:
               RGB_TO_YCBCR( color.r, color.g, color.b, y, u, v );
               R100_SET_YUV422_COLOR( rdrv, rdev, y, u, v );
          default:
               color3d = PIXEL_ARGB( color.a, color.r,
                                     color.g, color.b );
               break;
     }

     radeon_waitfifo( rdrv, rdev, 1 );
     radeon_out32( rdrv->mmio_base, PP_TFACTOR_0, color3d );

     RADEON_SET( COLOR );
}
