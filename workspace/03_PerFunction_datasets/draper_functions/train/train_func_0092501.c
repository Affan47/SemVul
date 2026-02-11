IDirectFBWindow_EnableEvents( IDirectFBWindow       *thiz,
                              DFBWindowEventType     mask )
{
     DIRECT_INTERFACE_GET_DATA(IDirectFBWindow)

     D_DEBUG_AT( IDirectFB_Window, "%s()\n", __FUNCTION__ );

     if (data->destroyed)
          return DFB_DESTROYED;

     if (mask & ~DWET_ALL)
          return DFB_INVARG;

     return dfb_window_change_events( data->window, DWET_NONE, mask );
}
