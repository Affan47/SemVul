IDirectFBWindow_SetSrcGeometry( IDirectFBWindow         *thiz,
                                const DFBWindowGeometry *geometry )
{
     DFBResult        ret;
     CoreWindowConfig config;

     DIRECT_INTERFACE_GET_DATA(IDirectFBWindow)

     D_DEBUG_AT( IDirectFB_Window, "%s()\n", __FUNCTION__ );

     ret = CheckGeometry( geometry );
     if (ret)
          return ret;

     if (data->destroyed)
          return DFB_DESTROYED;

     config.src_geometry = *geometry;

     return dfb_window_set_config( data->window, &config, CWCF_SRC_GEOMETRY );
}
