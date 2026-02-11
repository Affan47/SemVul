IDirectFBPalette_GetSize( IDirectFBPalette *thiz,
                          unsigned int     *size )
{
     CorePalette *palette;

     DIRECT_INTERFACE_GET_DATA(IDirectFBPalette)

     palette = data->palette;
     if (!palette)
          return DFB_DESTROYED;

     if (!size)
          return DFB_INVARG;

     *size = palette->num_entries;

     return DFB_OK;
}
