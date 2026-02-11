spicSetRegion( CoreLayer                  *layer,
               void                       *driver_data,
               void                       *layer_data,
               void                       *region_data,
               CoreLayerRegionConfig      *config,
               CoreLayerRegionConfigFlags  updated,
               CoreSurface                *surface,
               CorePalette                *palette,
               CoreSurfaceBufferLock      *lock )
{
     MatroxDriverData    *mdrv  = (MatroxDriverData*) driver_data;
     MatroxSpicLayerData *mspic = (MatroxSpicLayerData*) layer_data;
     MatroxDeviceData    *mdev  = mdrv->device_data;
     volatile u8         *mmio  = mdrv->mmio_base;


     mspic->config = *config;

     if (updated & CLRCF_PALETTE) {
          u8 y, cb, cr;
          int  i;

          for (i = 0; i < 16; i++) {
               RGB_TO_YCBCR( palette->entries[i].r,
                             palette->entries[i].g,
                             palette->entries[i].b,
                             y, cb, cr );

               mspic->regs.c2SUBPICLUT = (cr << 24) | (cb << 16) | (y << 8) | i;
               mga_out32( mmio, mspic->regs.c2SUBPICLUT, C2SUBPICLUT );
          }
     }

     if (updated & (CLRCF_WIDTH | CLRCF_HEIGHT | CLRCF_FORMAT | CLRCF_SURFACE_CAPS |
                    CLRCF_OPTIONS | CLRCF_OPACITY | CLRCF_SURFACE)) {
          spic_calc_buffer( mdrv, mspic, surface, lock );
          spic_set_buffer( mdrv, mspic );

          mspic->regs.c2DATACTL = mga_in32( mmio, C2DATACTL );

          if (surface->config.caps & DSCAPS_INTERLACED || mdev->crtc2_separated)
               mspic->regs.c2DATACTL &= ~C2OFFSETDIVEN;
          else
               mspic->regs.c2DATACTL |= C2OFFSETDIVEN;

          if (config->opacity)
               mspic->regs.c2DATACTL |= C2SUBPICEN;
          else
               mspic->regs.c2DATACTL &= ~C2SUBPICEN;

          if (config->options & DLOP_ALPHACHANNEL)
               mspic->regs.c2DATACTL &= ~C2STATICKEYEN;
          else
               mspic->regs.c2DATACTL |= C2STATICKEYEN;

          mspic->regs.c2DATACTL &= ~C2STATICKEY;
          mspic->regs.c2DATACTL |= ((config->opacity + 1) << 20) & C2STATICKEY;

          mga_out32( mmio, mspic->regs.c2DATACTL, C2DATACTL);
     }

     return DFB_OK;
}
