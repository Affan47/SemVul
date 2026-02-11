IDirectFBSurface_Window_Construct( IDirectFBSurface       *thiz,
                                   IDirectFBSurface       *parent,
                                   DFBRectangle           *wanted,
                                   DFBRectangle           *granted,
                                   CoreWindow             *window,
                                   DFBSurfaceCapabilities  caps,
                                   CoreDFB                *core )
{
     DFBResult        ret;
     DFBInsets        insets;
     CoreWindowStack *stack;

     DIRECT_ALLOCATE_INTERFACE_DATA(thiz, IDirectFBSurface_Window)

     D_DEBUG_AT( Surface, "%s( %p )\n", __FUNCTION__, thiz );

     stack = window->stack;
     D_MAGIC_ASSERT( stack, CoreWindowStack );

     dfb_layer_context_lock( stack->context );

     dfb_wm_get_insets( stack, window, &insets );

     dfb_layer_context_unlock( stack->context );

     ret = IDirectFBSurface_Construct( thiz, parent, wanted, granted, &insets,
                                       window->surface, caps, core );
     if (ret)
          return ret;

     if (dfb_window_ref( window )) {
          IDirectFBSurface_Destruct( thiz );
          return DFB_FAILURE;
     }

     data->window = window;
     data->flip_thread = (pthread_t) -1;


     if (!(caps & DSCAPS_FLIPPING) && !(caps & DSCAPS_SUBSURFACE)) {
          if (dfb_config->autoflip_window)
               pthread_create( &data->flip_thread, NULL, Flipping_Thread, thiz );
          else
               D_WARN( "Non-flipping window surface and no 'autoflip-window' option used" );
     }

     thiz->Release = IDirectFBSurface_Window_Release;
     thiz->Flip = IDirectFBSurface_Window_Flip;
     thiz->GetSubSurface = IDirectFBSurface_Window_GetSubSurface;

     return DFB_OK;
}
