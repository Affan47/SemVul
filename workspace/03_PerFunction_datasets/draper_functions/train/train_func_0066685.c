nv_set_blitting_color( NVidiaDriverData *nvdrv,
                            NVidiaDeviceData *nvdev,
                            CardState        *state )
{
     DFBColor color = state->color;

     if (NVIDIA_IS_SET( BLITTING_COLOR ) && NVIDIA_IS_SET( BLITTING_FLAGS ))
          return;

     if (state->blittingflags & (DSBLIT_COLORIZE | DSBLIT_SRC_PREMULTCOLOR) ||
        (state->blittingflags & DSBLIT_BLEND_ALPHACHANNEL && state->src_blend == DSBF_ONE)) {
          nvdev->color3d = (state->blittingflags & DSBLIT_BLEND_COLORALPHA)
                           ? (color.a << 24) : 0xFF000000;

          if (state->blittingflags & DSBLIT_COLORIZE &&
              state->blittingflags & (DSBLIT_SRC_PREMULTCOLOR | DSBLIT_BLEND_COLORALPHA)) {
               nvdev->color3d |= PIXEL_RGB32( color.r * color.a / 0xFF,
                                              color.g * color.a / 0xFF,
                                              color.b * color.a / 0xFF );
          }
          else if (state->blittingflags & DSBLIT_COLORIZE) {
               nvdev->color3d |= PIXEL_RGB32( color.r, color.g, color.b );
          }
          else if (state->blittingflags & (DSBLIT_SRC_PREMULTCOLOR | DSBLIT_BLEND_COLORALPHA)) {
               nvdev->color3d |= PIXEL_RGB32( color.a, color.a, color.a );
          }
          else {
               nvdev->color3d |= 0x00FFFFFF;
          }

          if (!nvdev->beta4_set || nvdev->beta4_val != nvdev->color3d) {
               nv_assign_object( nvdrv, nvdev,
                                 SUBC_BETA4, OBJ_BETA4, false );

               nv_begin( SUBC_BETA4, BETA4_FACTOR, 1 );
               nv_outr( nvdev->color3d );

               nvdev->beta4_val = nvdev->color3d;
               nvdev->beta4_set = true;
          }
     }
     else if (state->blittingflags & (DSBLIT_BLEND_COLORALPHA |
                                      DSBLIT_BLEND_ALPHACHANNEL)) {
          u32 beta1;

          if (state->blittingflags & DSBLIT_BLEND_COLORALPHA) {
               nvdev->color3d = (color.a << 24) | 0x00FFFFFF;
               beta1          =  color.a << 23;
          } else {
               nvdev->color3d = 0xFFFFFFFF;
               beta1          = 0x7F800000;
          }

          if (!nvdev->beta1_set || nvdev->beta1_val != beta1) {
               nv_assign_object( nvdrv, nvdev,
                                 SUBC_BETA1, OBJ_BETA1, false );

               nv_begin( SUBC_BETA1, BETA1_FACTOR, 1 );
               nv_outr( beta1 );

               nvdev->beta1_val = beta1;
               nvdev->beta1_set = true;
          }
     }

     NVIDIA_SET  ( BLITTING_COLOR );
     NVIDIA_UNSET( DRAWING_COLOR );
}
