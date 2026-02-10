IDirectFBImageProvider_DFIFF_GetSurfaceDescription( IDirectFBImageProvider *thiz,
                                                    DFBSurfaceDescription *dsc )
{
     const DFIFFHeader *header;

     DIRECT_INTERFACE_GET_DATA (IDirectFBImageProvider_DFIFF)

     header = data->ptr;

     dsc->flags       = DSDESC_WIDTH | DSDESC_HEIGHT | DSDESC_PIXELFORMAT;
     dsc->width       = header->width;
     dsc->height      = header->height;
     dsc->pixelformat = header->format;

     return DFB_OK;
}
