IDirectFBFont_GetDescender( IDirectFBFont *thiz, int *descender )
{
     DIRECT_INTERFACE_GET_DATA(IDirectFBFont)

     D_DEBUG_AT( Font, "%s( %p )\n", __FUNCTION__, thiz );

     if (!descender)
          return DFB_INVARG;

     *descender = data->font->descender;

     return DFB_OK;
}
