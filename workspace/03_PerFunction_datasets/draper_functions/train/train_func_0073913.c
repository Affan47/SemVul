dfb_layer_context_set_sourcerectangle( CoreLayerContext   *context,
                                       const DFBRectangle *source )
{
     DFBResult             ret;
     CoreLayerRegionConfig config;

     D_ASSERT( context != NULL );
     D_ASSERT( source != NULL );


     if (dfb_layer_context_lock( context ))
          return DFB_FUSION;


     config = context->primary.config;


     if (DFB_RECTANGLE_EQUAL( config.source, *source )) {
          dfb_layer_context_unlock( context );
          return DFB_OK;
     }


     if (source->x < 0 || source->y < 0 ||
         source->x + source->w > config.width ||
         source->y + source->h > config.height) {
          dfb_layer_context_unlock( context );
          return DFB_INVAREA;
     }


     config.source = *source;


     ret = update_primary_region_config( context, &config, CLRCF_SOURCE );


     dfb_layer_context_unlock( context );

     return ret;
}
