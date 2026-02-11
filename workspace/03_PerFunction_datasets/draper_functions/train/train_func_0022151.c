r300_set_src_colorkey( RadeonDriverData *rdrv,
                            RadeonDeviceData *rdev,
                            CardState        *state )
{
     volatile u8 *mmio = rdrv->mmio_base;
     u32          key  = state->src_colorkey;

     if (RADEON_IS_SET( SRC_COLORKEY ))
          return;

     switch (rdev->src_format) {
          case DSPF_ARGB4444:
               key |= 0xf000;
               break;
          case DSPF_ARGB2554:
               key |= 0xc000;
               break;
          case DSPF_ARGB1555:
               key |= 0x8000;
               break;
          case DSPF_ARGB:
          case DSPF_AYUV:
               key |= 0xff000000;
               break;
          default:
               break;
     }

     radeon_waitfifo( rdrv, rdev, 3 );
     radeon_out32( mmio, CLR_CMP_CLR_SRC, key );

     radeon_out32( mmio, CLR_CMP_MASK, rdev->src_mask );
     if (R300_HAS_3DREGS())
          radeon_out32( mmio, R300_TX_CHROMA_KEY_0, state->src_colorkey );

     RADEON_SET( SRC_COLORKEY );
}
