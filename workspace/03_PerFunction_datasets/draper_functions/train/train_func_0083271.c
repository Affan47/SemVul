IDirectFBWindow_GetProperty( IDirectFBWindow  *thiz,
                             const char       *key,
                             void            **ret_value )
{
     DFBResult ret;

     DIRECT_INTERFACE_GET_DATA(IDirectFBWindow)

     D_DEBUG_AT( IDirectFB_Window, "%s()\n", __FUNCTION__ );

     if (data->destroyed)
          return DFB_DESTROYED;

     if (!key)
          return DFB_INVARG;

     if (!ret_value)
          return DFB_INVARG;

     dfb_windowstack_lock( data->window->stack );
     ret = dfb_wm_get_window_property( data->window->stack, data->window, key, ret_value );
     dfb_windowstack_unlock( data->window->stack );

     return ret;
}
