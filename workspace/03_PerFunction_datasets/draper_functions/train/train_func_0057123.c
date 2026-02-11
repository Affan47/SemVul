wm_request_focus( CoreWindow *window,
                  void       *wm_data,
                  void       *window_data )
{
     WindowData *data = window_data;

     D_ASSERT( window != NULL );
     D_ASSERT( wm_data != NULL );
     D_ASSERT( window_data != NULL );

     D_MAGIC_ASSERT( data, WindowData );

     if (!data->window)
          return DFB_DESTROYED;

     return unique_window_request_focus( data->window );
}
