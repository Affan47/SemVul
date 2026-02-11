r300_set_clip( RadeonDriverData *rdrv,
                    RadeonDeviceData *rdev,
                    CardState        *state )
{
     DFBRegion   *clip = &state->clip;
     volatile u8 *mmio = rdrv->mmio_base;

     if (RADEON_IS_SET( CLIP ))
          return;


     radeon_waitfifo( rdrv, rdev, 2 );
     if (rdev->dst_422) {
          radeon_out32( mmio, SC_TOP_LEFT,
                      (clip->y1 << 16) | (clip->x1/2 & 0xffff) );
          radeon_out32( mmio, SC_BOTTOM_RIGHT,
                      ((clip->y2+1) << 16) | ((clip->x2+1)/2 & 0xffff) );
     } else {
          radeon_out32( mmio, SC_TOP_LEFT,
                      (clip->y1 << 16) | (clip->x1 & 0xffff) );
          radeon_out32( mmio, SC_BOTTOM_RIGHT,
                      ((clip->y2+1) << 16) | ((clip->x2+1) & 0xffff) );
     }


     if (R300_HAS_3DREGS())
          r300_set_clip3d( rdrv, rdev, clip );

     rdev->clip = state->clip;

     RADEON_SET( CLIP );
}
