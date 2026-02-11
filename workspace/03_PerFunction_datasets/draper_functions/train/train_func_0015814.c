primarySetRegion( CoreLayer                  *layer,
                  void                       *driver_data,
                  void                       *layer_data,
                  void                       *region_data,
                  CoreLayerRegionConfig      *config,
                  CoreLayerRegionConfigFlags  updated,
                  CoreSurface                *surface,
                  CorePalette                *palette,
                  CoreSurfaceBufferLock      *lock )
{
     DFBResult    ret;
     FBDevShared *shared = dfb_fbdev->shared;

     if (updated & CLRCF_SOURCE) {
          if (config->source.w == shared->current_var.xres && config->source.h == shared->current_var.yres) {
               ret = dfb_fbdev_pan( config->source.x, lock->offset / lock->pitch + config->source.y, true );
               if (ret)
                    return ret;
          }
          else {
               const VideoMode *mode;

               D_INFO( "FBDev/Mode: Setting %dx%d %s\n", config->source.w, config->source.h,
                       dfb_pixelformat_name( surface->config.format ) );

               mode = dfb_fbdev_find_mode( config->source.w, config->source.h );
               if (!mode)
                    return DFB_UNSUPPORTED;

               ret = dfb_fbdev_set_mode( mode, surface, config->source.x,
                                         lock->offset / lock->pitch + config->source.y );
               if (ret)
                    return ret;
          }
     }

     if ((updated & CLRCF_PALETTE) && palette)
          dfb_fbdev_set_palette( palette );


     shared->config = *config;

     return DFB_OK;
}
