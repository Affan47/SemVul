IDirectFBDisplayLayer_SetSrcColorKey( IDirectFBDisplayLayer *thiz,
                                      u8                     r,
                                      u8                     g,
                                      u8                     b )
{
     DIRECT_INTERFACE_GET_DATA(IDirectFBDisplayLayer)

     if (data->level == DLSCL_SHARED)
          return DFB_ACCESSDENIED;

     return dfb_layer_context_set_src_colorkey( data->context, r, g, b, -1 );
}
