IDirectFBSurface_GetFramebufferOffset( IDirectFBSurface *thiz,
                                       int *offset )
{
     DIRECT_INTERFACE_GET_DATA(IDirectFBSurface)

     if (!data->surface)
          return DFB_DESTROYED;

     if (!offset)
          return DFB_INVARG;

     if (!data->locked)
          return DFB_ACCESSDENIED;

     if (!data->lock.phys) {

          return DFB_UNSUPPORTED;
     }

     *offset = data->lock.offset;

     return DFB_OK;
}
