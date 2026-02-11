dfb_x11_destroy_window( DFBX11 *x11 )
{
     int           ret;
     DFBX11Shared *shared = x11->shared;

     if (fusion_call_execute( &shared->call, FCEF_NONE, X11_DESTROY_WINDOW, NULL, &ret ))
          return DFB_FUSION;

     return ret;
}
