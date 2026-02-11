ps30_input_emit_depth_fog( struct svga_shader_emitter *emit,
                           struct src_register *out )
{
   struct src_register reg;

   if (emit->emitted_depth_fog) {
      *out = emit->ps_depth_fog;
      return TRUE;
   }

   if (emit->ps30_input_count >= SVGA3D_INPUTREG_MAX)
      return FALSE;

   reg = src_register( SVGA3DREG_INPUT,
                       emit->ps30_input_count++ );

   *out = emit->ps_depth_fog = reg;

   emit->emitted_depth_fog = TRUE;

   return emit_decl( emit, dst( reg ), SVGA3D_DECLUSAGE_TEXCOORD, 0 );
}
