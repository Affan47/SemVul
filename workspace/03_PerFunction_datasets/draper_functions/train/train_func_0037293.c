IDirectFBSurface_Release( IDirectFBSurface *thiz )
{
     DIRECT_INTERFACE_GET_DATA(IDirectFBSurface)

     D_DEBUG_AT( Surface, "%s( %p )\n", __FUNCTION__, thiz );

     if (--data->ref == 0)
          IDirectFBSurface_Destruct( thiz );

     return DFB_OK;
}
