create_shader(struct gl_context *ctx, GLenum type)
{
   struct gl_shader *sh;
   GLuint name;

   if (!_mesa_validate_shader_target(ctx, type)) {
      _mesa_error(ctx, GL_INVALID_ENUM, "CreateShader(type)");
      return 0;
   }

   name = _mesa_HashFindFreeKeyBlock(ctx->Shared->ShaderObjects, 1);
   sh = ctx->Driver.NewShader(ctx, name, type);
   _mesa_HashInsert(ctx->Shared->ShaderObjects, name, sh);

   return name;
}
