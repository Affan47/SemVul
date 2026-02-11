dfb_windowstack_set_background_mode ( CoreWindowStack               *stack,
                                      DFBDisplayLayerBackgroundMode  mode )
{
     D_DEBUG_AT( Core_WindowStack, "%s( %p, %d )\n", __FUNCTION__, stack, mode );

     D_MAGIC_ASSERT( stack, CoreWindowStack );


     if (dfb_windowstack_lock( stack ))
          return DFB_FUSION;


     if (mode != stack->bg.mode) {

          if ((mode == DLBM_IMAGE || mode == DLBM_TILE) && !stack->bg.image) {
               dfb_windowstack_unlock( stack );
               return DFB_MISSINGIMAGE;
          }


          stack->bg.mode = mode;


          if (mode != DLBM_DONTCARE)
               dfb_windowstack_repaint_all( stack );
     }


     dfb_windowstack_unlock( stack );

     return DFB_OK;
}
