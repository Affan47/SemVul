_mesa_validate_MultiDrawArraysIndirect(struct gl_context *ctx,
                                       GLenum mode,
                                       const GLvoid *indirect,
                                       GLsizei primcount, GLsizei stride)
{
   GLsizeiptr size = 0;
   const unsigned drawArraysNumParams = 4;

   FLUSH_CURRENT(ctx, 0);


   assert(stride != 0);

   if (!valid_draw_indirect_multi(ctx, primcount, stride,
                                  "glMultiDrawArraysIndirect"))
      return GL_FALSE;


   size = primcount
      ? (primcount - 1) * stride + drawArraysNumParams * sizeof(GLuint)
      : 0;

   if (!valid_draw_indirect(ctx, mode, indirect, size,
                            "glMultiDrawArraysIndirect"))
      return GL_FALSE;

   return GL_TRUE;
}
