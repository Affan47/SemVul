osdTestRegion( CoreLayer                  *layer,
               void                       *driver_data,
               void                       *layer_data,
               CoreLayerRegionConfig      *config,
               CoreLayerRegionConfigFlags *failed )
{
     DFBResult                  ret;
     CoreLayerRegionConfigFlags fail = 0;
     DFBDisplayLayerOptions     options = config->options;


     config->options = DLOP_NONE;


     ret = oldPrimaryFuncs.TestRegion( layer, oldPrimaryDriverData,
                                       layer_data, config, &fail );


     if (options) {

          if (options & ~OSD_OPTIONS)
               fail |= CLRCF_OPTIONS;


          if ((options & (DLOP_OPACITY | DLOP_ALPHACHANNEL)) ==
              (DLOP_OPACITY | DLOP_ALPHACHANNEL))
          {
               fail |= CLRCF_OPTIONS;
          }
     }


     config->options = options;

     if (failed)
          *failed = fail;

     if (fail)
          return DFB_UNSUPPORTED;

     return ret;
}
