_mesa_ProgramEnvParameter4fARB(GLenum target, GLuint index,
                               GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
   GLfloat *param;

   GET_CURRENT_CONTEXT(ctx);

   FLUSH_VERTICES(ctx, _NEW_PROGRAM_CONSTANTS);

   if (get_env_param_pointer(ctx, "glProgramEnvParameter",
			     target, index, &param)) {
      ASSIGN_4V(param, x, y, z, w);
   }
}
