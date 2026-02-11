IDirectFBWindow_SetColor( IDirectFBWindow *thiz,
                          u8               r,
                          u8               g,
                          u8               b,
                          u8               a )
{
     DFBColor color = { a: a, r: r, g: g, b: b };

     DIRECT_INTERFACE_GET_DATA(IDirectFBWindow)

     D_DEBUG_AT( IDirectFB_Window, "%s()\n", __FUNCTION__ );

     if (data->destroyed)
          return DFB_DESTROYED;

     dfb_window_set_color( data->window, color );

     return DFB_OK;
}
