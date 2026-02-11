IDirectFBVideoProvider_GIF_GetSurfaceDescription( IDirectFBVideoProvider *thiz,
                                                  DFBSurfaceDescription  *desc )
{
     DIRECT_INTERFACE_GET_DATA( IDirectFBVideoProvider_GIF )

     if (!desc)
          return DFB_INVARG;

     desc->flags       = DSDESC_WIDTH | DSDESC_HEIGHT | DSDESC_PIXELFORMAT;
     desc->width       = data->Width;
     desc->height      = data->Height;
     desc->pixelformat = DSPF_ARGB;

     return DFB_OK;
}
