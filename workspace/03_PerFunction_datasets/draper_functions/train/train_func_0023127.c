dfb_window_raisetotop( CoreWindow *window )
{
     DFBResult        ret;
     CoreWindowStack *stack;

     D_ASSERT( window != NULL );
     D_ASSERT( window->stack != NULL );

     stack = window->stack;


     if (dfb_windowstack_lock( stack ))
          return DFB_FUSION;


     if (DFB_WINDOW_DESTROYED( window )) {
          dfb_windowstack_unlock( stack );
          return DFB_DESTROYED;
     }


     ret = dfb_wm_restack_window( window, NULL, 1 );


     dfb_windowstack_unlock( stack );

     return ret;
}
