crtc2SetRegion( CoreLayer                  *layer,
                void                       *driver_data,
                void                       *layer_data,
                void                       *region_data,
                CoreLayerRegionConfig      *config,
                CoreLayerRegionConfigFlags  updated,
                CoreSurface                *surface,
                CorePalette                *palette,
                CoreSurfaceBufferLock      *lock )
{
     RadeonDriverData     *rdrv   = (RadeonDriverData*) driver_data;
     RadeonCrtc2LayerData *rcrtc2 = (RadeonCrtc2LayerData*) layer_data;

     rcrtc2->config  = *config;
     rcrtc2->palette = palette;

     updated &= CLRCF_WIDTH  | CLRCF_HEIGHT  |
                CLRCF_FORMAT | CLRCF_SURFACE | CLRCF_PALETTE;

     if (updated & ~CLRCF_PALETTE) {
          if (!crtc2_calc_regs( rdrv, rcrtc2, &rcrtc2->config, surface, lock ))
               return DFB_UNSUPPORTED;

          crtc2_set_regs( rdrv, rcrtc2 );
     }

     if (updated) {
          crtc2_calc_palette( rdrv, rcrtc2, &rcrtc2->config,
                              &rcrtc2->adjustment, rcrtc2->palette );
          crtc2_set_palette( rdrv, rcrtc2 );
     }

     return DFB_OK;
}
