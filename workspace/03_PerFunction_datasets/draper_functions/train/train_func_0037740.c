IDirectFBDisplayLayer_GetSurface( IDirectFBDisplayLayer  *thiz,
                                  IDirectFBSurface      **interface )
{
     DFBResult         ret;
     CoreLayerRegion  *region;
     IDirectFBSurface *surface;

     DIRECT_INTERFACE_GET_DATA(IDirectFBDisplayLayer)

     if (!interface)
          return DFB_INVARG;

     if (data->level == DLSCL_SHARED) {
          D_WARN( "letting unprivileged IDirectFBDisplayLayer::GetSurface() "
                   "call pass until cooperative level handling is finished" );
     }

     ret = dfb_layer_context_get_primary_region( data->context, true, &region );
     if (ret)
          return ret;

     DIRECT_ALLOCATE_INTERFACE( surface, IDirectFBSurface );

     ret = IDirectFBSurface_Layer_Construct( surface, NULL, NULL, NULL,
                                             region, DSCAPS_NONE, data->core );

     if (region->config.buffermode == DLBM_FRONTONLY && data->level == DLSCL_EXCLUSIVE) {
          surface->Clear( surface, 0, 0, 0, 0 );
          dfb_layer_region_flip_update( region, NULL, DSFLIP_NONE );
     }

     *interface = ret ? NULL : surface;

     dfb_layer_region_unref( region );

     return ret;
}
