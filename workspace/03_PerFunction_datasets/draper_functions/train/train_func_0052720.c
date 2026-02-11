_mesa_GetActiveUniform(GLhandleARB program, GLuint index,
                          GLsizei maxLength, GLsizei *length, GLint *size,
                          GLenum *type, GLcharARB *nameOut)
{
   GET_CURRENT_CONTEXT(ctx);
   struct gl_shader_program *shProg =
      _mesa_lookup_shader_program_err(ctx, program, "glGetActiveUniform");

   if (!shProg)
      return;

   if (index >= shProg->NumUserUniformStorage) {
      _mesa_error(ctx, GL_INVALID_VALUE, "glGetActiveUniform(index)");
      return;
   }

   const struct gl_uniform_storage *const uni = &shProg->UniformStorage[index];

   if (nameOut) {
      _mesa_get_uniform_name(uni, maxLength, length, nameOut);
   }

   if (size) {


      *size = MAX2(1, uni->array_elements);
   }

   if (type) {
      *type = uni->type->gl_type;
   }
}
