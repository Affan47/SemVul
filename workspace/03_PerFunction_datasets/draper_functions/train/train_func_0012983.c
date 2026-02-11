spicTestRegion( CoreLayer                  *layer,
                void                       *driver_data,
                void                       *layer_data,
                CoreLayerRegionConfig      *config,
                CoreLayerRegionConfigFlags *failed )
{
     CoreLayerRegionConfigFlags fail = 0;

     if (config->options & ~SPIC_SUPPORTED_OPTIONS)
          fail |= CLRCF_OPTIONS;


     if (config->options & DLOP_ALPHACHANNEL && config->options & DLOP_OPACITY)
          fail |= CLRCF_OPTIONS;

     switch (config->opacity) {
          case 0x00:
          case 0xFF:
               break;
          default:
               if (!(config->options & DLOP_OPACITY))
                    fail |= CLRCF_OPACITY;
     }

     if (config->surface_caps & ~(DSCAPS_INTERLACED | DSCAPS_SEPARATED))
          fail |= CLRCF_SURFACE_CAPS;

     if (config->format != DSPF_ALUT44)
          fail |= CLRCF_FORMAT;

     if (config->width != 720)
          fail |= CLRCF_WIDTH;

     if (config->surface_caps & DSCAPS_INTERLACED) {
          if (config->height != ((dfb_config->matrox_tv_std != DSETV_PAL) ? 480 : 576))
               fail |= CLRCF_HEIGHT;
     } else {
          if (config->height != ((dfb_config->matrox_tv_std != DSETV_PAL) ? 240 : 288))
               fail |= CLRCF_HEIGHT;
     }

     if (failed)
          *failed = fail;

     if (fail)
          return DFB_UNSUPPORTED;

     return DFB_OK;
}
