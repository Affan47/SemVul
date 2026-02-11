_save_OBE_DrawArrays(GLenum mode, GLint start, GLsizei count)
{
   GET_CURRENT_CONTEXT(ctx);
   struct vbo_save_context *save = &vbo_context(ctx)->save;
   GLint i;

   if (!_mesa_is_valid_prim_mode(ctx, mode)) {
      _mesa_compile_error(ctx, GL_INVALID_ENUM, "glDrawArrays(mode)");
      return;
   }
   if (count < 0) {
      _mesa_compile_error(ctx, GL_INVALID_VALUE, "glDrawArrays(count<0)");
      return;
   }

   if (save->out_of_memory)
      return;

   _ae_map_vbos(ctx);

   vbo_save_NotifyBegin(ctx, (mode | VBO_SAVE_PRIM_WEAK
                              | VBO_SAVE_PRIM_NO_CURRENT_UPDATE));

   for (i = 0; i < count; i++)
      CALL_ArrayElement(GET_DISPATCH(), (start + i));
   CALL_End(GET_DISPATCH(), ());

   _ae_unmap_vbos(ctx);
}
