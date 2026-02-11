dfb_gfx_copy_to( CoreSurface *source, CoreSurface *destination, const DFBRectangle *rect, int x, int y, bool from_back )
{
     DFBRectangle sourcerect = { 0, 0, source->config.size.w, source->config.size.h };

     pthread_mutex_lock( &copy_lock );

     if (!copy_state_inited) {
          dfb_state_init( &copy_state, NULL );
          copy_state_inited = true;
     }

     copy_state.modified   |= SMF_CLIP | SMF_SOURCE | SMF_DESTINATION;

     copy_state.clip.x2     = destination->config.size.w - 1;
     copy_state.clip.y2     = destination->config.size.h - 1;
     copy_state.source      = source;
     copy_state.destination = destination;
     copy_state.from        = from_back ? CSBR_BACK : CSBR_FRONT;

     if (rect) {
          if (dfb_rectangle_intersect( &sourcerect, rect ))
               dfb_gfxcard_blit( &sourcerect,
                                 x + sourcerect.x - rect->x,
                                 y + sourcerect.y - rect->y, &copy_state );
     }
     else
          dfb_gfxcard_blit( &sourcerect, x, y, &copy_state );


     dfb_state_stop_drawing( &copy_state );

     pthread_mutex_unlock( &copy_lock );
}
