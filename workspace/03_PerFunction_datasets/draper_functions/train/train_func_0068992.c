set_sampler_compare_func(struct gl_context *ctx,
                         struct gl_sampler_object *samp, GLint param)
{
   if (!ctx->Extensions.ARB_shadow)
      return INVALID_PNAME;

   if (samp->CompareFunc == param)
      return GL_FALSE;

   switch (param) {
   case GL_LEQUAL:
   case GL_GEQUAL:
   case GL_EQUAL:
   case GL_NOTEQUAL:
   case GL_LESS:
   case GL_GREATER:
   case GL_ALWAYS:
   case GL_NEVER:
      flush(ctx);
      samp->CompareFunc = param;
      return GL_TRUE;
   default:
      return INVALID_PARAM;
   }
}
