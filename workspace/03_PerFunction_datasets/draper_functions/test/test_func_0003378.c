_mesa_IsEnabledi( GLenum cap, GLuint index )
{
   GET_CURRENT_CONTEXT(ctx);
   ASSERT_OUTSIDE_BEGIN_END_WITH_RETVAL(ctx, 0);
   switch (cap) {
   case GL_BLEND:
      if (index >= ctx->Const.MaxDrawBuffers) {
         _mesa_error(ctx, GL_INVALID_VALUE, "glIsEnabledIndexed(index=%u)",
                     index);
         return GL_FALSE;
      }
      return (ctx->Color.BlendEnabled >> index) & 1;
   case GL_SCISSOR_TEST:
      if (index >= ctx->Const.MaxViewports) {
         _mesa_error(ctx, GL_INVALID_VALUE, "glIsEnabledIndexed(index=%u)",
                     index);
         return GL_FALSE;
      }
      return (ctx->Scissor.EnableFlags >> index) & 1;
   default:
      _mesa_error(ctx, GL_INVALID_ENUM, "glIsEnabledIndexed(cap=%s)",
                  _mesa_lookup_enum_by_nr(cap));
      return GL_FALSE;
   }
}
