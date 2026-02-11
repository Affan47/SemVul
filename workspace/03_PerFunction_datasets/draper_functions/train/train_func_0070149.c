IDirectFBDisplayLayer_SetCursorShape( IDirectFBDisplayLayer *thiz,
                                      IDirectFBSurface      *shape,
                                      int                    hot_x,
                                      int                    hot_y )
{
     IDirectFBSurface_data *shape_data;

     DIRECT_INTERFACE_GET_DATA(IDirectFBDisplayLayer)

     if (!shape)
          return DFB_INVARG;

     if (data->level == DLSCL_SHARED)
          return DFB_ACCESSDENIED;

     shape_data = (IDirectFBSurface_data*)shape->priv;

     if (hot_x < 0  ||
         hot_y < 0  ||
         hot_x >= shape_data->surface->config.size.w  ||
         hot_y >= shape_data->surface->config.size.h)
          return DFB_INVARG;

     return dfb_windowstack_cursor_set_shape( data->stack,
                                              shape_data->surface,
                                              hot_x, hot_y );
}
