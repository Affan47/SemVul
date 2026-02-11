nv20CheckState( void *drv, void *dev,
                            CardState *state, DFBAccelerationMask accel )
{
     CoreSurface *destination = state->destination;
     CoreSurface *source      = state->source;

     switch (destination->config.format) {
          case DSPF_A8:
          case DSPF_LUT8:
          case DSPF_ALUT44:
          case DSPF_RGB332:
               if (DFB_BLITTING_FUNCTION( accel )) {
                    if (state->blittingflags != DSBLIT_NOFX  ||
                        source->config.format != destination->config.format)
                         return;
               } else {
                    if (state->drawingflags != DSDRAW_NOFX)
                         return;
               }
               break;

          case DSPF_RGB555:
          case DSPF_ARGB1555:
          case DSPF_RGB16:
          case DSPF_RGB32:
          case DSPF_ARGB:
               break;

          case DSPF_YUY2:
          case DSPF_UYVY:
               if (DFB_BLITTING_FUNCTION( accel )) {
                    if (accel & ~(DFXL_BLIT | DFXL_STRETCHBLIT) ||
                        state->blittingflags != DSBLIT_NOFX     ||
                        source->config.format != destination->config.format)
                         return;
               } else {
                    if (accel & (DFXL_FILLTRIANGLE | DFXL_DRAWLINE) ||
                        state->drawingflags != DSDRAW_NOFX)
                         return;
               }
               break;

          default:
               return;
     }

     if (DFB_BLITTING_FUNCTION( accel )) {

          if (accel & ~NV20_SUPPORTED_BLITTINGFUNCTIONS ||
              state->blittingflags & ~NV20_SUPPORTED_BLITTINGFLAGS)
               return;

          if (state->blittingflags & DSBLIT_BLEND_ALPHACHANNEL) {
               if (state->blittingflags & DSBLIT_MODULATE_COLOR) {
                    if (source->config.format == DSPF_ARGB && state->src_blend != DSBF_ONE)
                         return;
               }

               if (state->src_blend != DSBF_ONE &&
                   state->src_blend != DSBF_SRCALPHA)
                    return;

               if (state->dst_blend != DSBF_INVSRCALPHA)
                    return;
          }

          if (state->render_options & DSRO_MATRIX &&
             (state->matrix[0] < 0 || state->matrix[1] ||
              state->matrix[3] || state->matrix[4] < 0))
                    return;

          switch (source->config.format) {
               case DSPF_A8:


                    break;

               case DSPF_LUT8:
               case DSPF_ALUT44:
                    if (destination->config.format != source->config.format ||

                        !dfb_palette_equal( source->palette,
                                            destination->palette ))
                         return;
                    break;

               case DSPF_RGB332:
                    if (destination->config.format != source->config.format
)
                         return;
                    break;

               case DSPF_RGB555:
               case DSPF_ARGB1555:
               case DSPF_RGB16:
               case DSPF_RGB32:
               case DSPF_ARGB:


                    break;

               case DSPF_YUY2:
               case DSPF_UYVY:


                    break;

               default:
                    return;
          }

          state->accel |= accel;
     }
     else {

          if (accel & ~NV20_SUPPORTED_DRAWINGFUNCTIONS ||
              state->drawingflags & ~NV20_SUPPORTED_DRAWINGFLAGS)
               return;

          if (state->drawingflags & DSDRAW_BLEND &&
              state->src_blend != DSBF_SRCALPHA  &&
              state->dst_blend != DSBF_INVSRCALPHA)
               return;

          state->accel |= NV20_SUPPORTED_DRAWINGFUNCTIONS;
     }
}
