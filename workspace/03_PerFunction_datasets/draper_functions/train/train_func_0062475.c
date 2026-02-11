emit_vface_decl(struct svga_shader_emitter *emit)
{
   if (!emit->emitted_vface) {
      SVGA3dShaderDestToken reg =
         dst_register(SVGA3DREG_MISCTYPE, SVGA3DMISCREG_FACE);

      if (!emit_decl( emit, reg, 0, 0 ))
         return FALSE;

      emit->emitted_vface = TRUE;
   }
   return TRUE;
}
