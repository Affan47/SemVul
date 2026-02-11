dfb_surface_read_buffer( CoreSurface            *surface,
                         CoreSurfaceBufferRole   role,
                         void                   *destination,
                         int                     pitch,
                         const DFBRectangle     *rect )
{
     DFBResult          ret;
     CoreSurfaceBuffer *buffer;

     D_MAGIC_ASSERT( surface, CoreSurface );
     D_ASSERT( destination != NULL );
     D_ASSERT( pitch > 0 );
     DFB_RECTANGLE_ASSERT_IF( rect );

     if (surface->num_buffers == 0)
          return DFB_SUSPENDED;

     if (fusion_skirmish_prevail( &surface->lock ))
          return DFB_FUSION;

     buffer = dfb_surface_get_buffer( surface, role );
     D_MAGIC_ASSERT( buffer, CoreSurfaceBuffer );

     ret = dfb_surface_buffer_read( buffer, destination, pitch, rect );

     fusion_skirmish_dismiss( &surface->lock );

     return ret;
}
