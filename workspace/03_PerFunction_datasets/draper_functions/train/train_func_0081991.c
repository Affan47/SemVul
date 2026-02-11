_mesa_AlphaFunc( GLenum func, GLclampf ref )
{
   GET_CURRENT_CONTEXT(ctx);

   if (MESA_VERBOSE & VERBOSE_API)
      _mesa_debug(ctx, "glAlphaFunc(%s, %f)\n",
                  _mesa_lookup_enum_by_nr(func), ref);

   switch (func) {
   case GL_NEVER:
   case GL_LESS:
   case GL_EQUAL:
   case GL_LEQUAL:
   case GL_GREATER:
   case GL_NOTEQUAL:
   case GL_GEQUAL:
   case GL_ALWAYS:
      if (ctx->Color.AlphaFunc == func && ctx->Color.AlphaRefUnclamped == ref)
         return;

      FLUSH_VERTICES(ctx, _NEW_COLOR);
      ctx->Color.AlphaFunc = func;
      ctx->Color.AlphaRefUnclamped = ref;
      ctx->Color.AlphaRef = CLAMP(ref, 0.0F, 1.0F);

      if (ctx->Driver.AlphaFunc)
         ctx->Driver.AlphaFunc(ctx, func, ctx->Color.AlphaRef);
      return;

   default:
      _mesa_error( ctx, GL_INVALID_ENUM, "glAlphaFunc(func)" );
      return;
   }
}
