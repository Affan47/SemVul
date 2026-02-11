_mesa_read_profile(struct _mesa_glsl_parse_state *state,
                   int profile_index,
		   const char *prototypes,
		   const char **functions,
                   int count)
{
   gl_shader *sh = builtin_profiles[profile_index];

   if (sh == NULL) {
      sh = read_builtins(GL_VERTEX_SHADER, prototypes, functions, count);
      ralloc_steal(builtin_mem_ctx, sh);
      builtin_profiles[profile_index] = sh;
   }

   state->builtins_to_link[state->num_builtins_to_link] = sh;
   state->num_builtins_to_link++;
}
