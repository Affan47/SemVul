IDirectFBWindow_SetColorKeyIndex( IDirectFBWindow *thiz,
                                  unsigned int     index )
{
     u32 key = index;

     DIRECT_INTERFACE_GET_DATA(IDirectFBWindow)

     D_DEBUG_AT( IDirectFB_Window, "%s()\n", __FUNCTION__ );

     if (data->destroyed)
          return DFB_DESTROYED;

     if (data->window->caps & DWCAPS_INPUTONLY)
          return DFB_UNSUPPORTED;

     return dfb_window_set_colorkey( data->window, key );
}
