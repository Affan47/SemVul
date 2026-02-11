IDirectFBDisplayLayer_GetSourceDescriptions( IDirectFBDisplayLayer            *thiz,
                                             DFBDisplayLayerSourceDescription *ret_descriptions )
{
     int i;

     DIRECT_INTERFACE_GET_DATA(IDirectFBDisplayLayer)

     if (!ret_descriptions)
          return DFB_INVARG;

     if (! D_FLAGS_IS_SET( data->desc.caps, DLCAPS_SOURCES ))
          return DFB_UNSUPPORTED;

     for (i=0; i<data->desc.sources; i++)
          dfb_layer_get_source_info( data->layer, i, &ret_descriptions[i] );

     return DFB_OK;
}
