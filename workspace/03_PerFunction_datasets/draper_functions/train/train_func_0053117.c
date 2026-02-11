IDirectFBSurface_SetEncoding( IDirectFBSurface  *thiz,
                              DFBTextEncodingID  encoding )
{
     DIRECT_INTERFACE_GET_DATA(IDirectFBSurface)

     D_DEBUG_AT( Surface, "%s( %p, %d )\n", __FUNCTION__, thiz, encoding );


     data->encoding = encoding;

     return DFB_OK;
}
