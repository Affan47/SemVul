dump_primary_layer_surface( CoreDFB *core )
{
     CoreLayer        *layer = dfb_layer_at( DLID_PRIMARY );
     CoreLayerContext *context;


     if (dfb_layer_get_active_context( layer, &context ) == DFB_OK) {
          CoreLayerRegion *region;


          if (dfb_layer_context_get_primary_region( context,
                                                    false, &region ) == DFB_OK)
          {
               CoreSurface *surface;


               dfb_layer_region_lock( region );


               if (dfb_layer_region_get_surface( region, &surface ) == DFB_OK) {

                    dfb_surface_dump_buffer( surface, CSBR_FRONT, dfb_config->screenshot_dir, "dfb" );


                    dfb_surface_unref( surface );
               }


               dfb_layer_region_unlock( region );


               dfb_layer_region_unref( region );
          }


          dfb_layer_context_unref( context );
     }
}
