IDirectFBSurface_GetCapabilities( IDirectFBSurface       *thiz,
                                  DFBSurfaceCapabilities *caps )
{
     DIRECT_INTERFACE_GET_DATA(IDirectFBSurface)

     D_DEBUG_AT( Surface, "%s( %p )\n", __FUNCTION__, thiz );

     if (!caps)
          return DFB_INVARG;

     *caps = data->caps;

     return DFB_OK;
}
