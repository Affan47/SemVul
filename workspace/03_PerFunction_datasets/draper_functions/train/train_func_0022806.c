save_TexSubImage1D(GLenum target, GLint level, GLint xoffset,
                   GLsizei width, GLenum format, GLenum type,
                   const GLvoid * pixels)
{
   GET_CURRENT_CONTEXT(ctx);
   Node *n;

   ASSERT_OUTSIDE_SAVE_BEGIN_END_AND_FLUSH(ctx);

   n = alloc_instruction(ctx, OPCODE_TEX_SUB_IMAGE1D, 6 + POINTER_DWORDS);
   if (n) {
      n[1].e = target;
      n[2].i = level;
      n[3].i = xoffset;
      n[4].i = (GLint) width;
      n[5].e = format;
      n[6].e = type;
      save_pointer(&n[7],
                   unpack_image(ctx, 1, width, 1, 1, format, type,
                                pixels, &ctx->Unpack));
   }
   if (ctx->ExecuteFlag) {
      CALL_TexSubImage1D(ctx->Exec, (target, level, xoffset, width,
                                     format, type, pixels));
   }
}
