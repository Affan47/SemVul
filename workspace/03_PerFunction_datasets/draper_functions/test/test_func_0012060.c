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
     DFBResult             ret;
     MatroxDriverData     *mdrv   = (MatroxDriverData*) driver_data;
     MatroxCrtc2LayerData *mcrtc2 = (MatroxCrtc2LayerData*) layer_data;
     MatroxDeviceData     *mdev   = mdrv->device_data;


     mcrtc2->config = *config;

     if (updated & CLRCF_PARITY)
          mcrtc2->field = !config->parity;

     if (updated & (CLRCF_WIDTH | CLRCF_HEIGHT | CLRCF_FORMAT |
                    CLRCF_SURFACE_CAPS | CLRCF_ALPHA_RAMP | CLRCF_SURFACE)) {
          crtc2_calc_regs( mdrv, mcrtc2, config, surface, lock );
          crtc2_calc_buffer( mdrv, mcrtc2, surface, lock );

          ret = crtc2_enable_output( mdrv, mcrtc2 );
          if (ret)
               return ret;

          mdev->crtc2_separated = !!(surface->config.caps & DSCAPS_SEPARATED);
     }

     return DFB_OK;
}
