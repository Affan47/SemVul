_tnl_invalidate_vertex_state( struct gl_context *ctx, GLuint new_state )
{

   if (new_state & (_NEW_LIGHT | _NEW_POLYGON) ) {
      struct tnl_clipspace *vtx = GET_VERTEX_STATE(ctx);
      vtx->new_inputs = ~0;
      vtx->interp = choose_interp_func;
      vtx->copy_pv = choose_copy_pv_func;
   }
}
