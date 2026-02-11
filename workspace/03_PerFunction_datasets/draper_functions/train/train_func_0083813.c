save_PixelMapfv(GLenum map, GLint mapsize, const GLfloat *values)
{
   GET_CURRENT_CONTEXT(ctx);
   Node *n;
   ASSERT_OUTSIDE_SAVE_BEGIN_END_AND_FLUSH(ctx);
   n = alloc_instruction(ctx, OPCODE_PIXEL_MAP, 2 + POINTER_DWORDS);
   if (n) {
      n[1].e = map;
      n[2].i = mapsize;
      save_pointer(&n[3], memdup(values, mapsize * sizeof(GLfloat)));
   }
   if (ctx->ExecuteFlag) {
      CALL_PixelMapfv(ctx->Exec, (map, mapsize, values));
   }
}
