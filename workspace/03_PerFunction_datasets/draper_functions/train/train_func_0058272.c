generate_100ES_vs_variables(exec_list *instructions,
			  struct _mesa_glsl_parse_state *state)
{
   for (unsigned i = 0; i < Elements(builtin_core_vs_variables); i++) {
      add_builtin_variable(instructions, state->symbols,
			   & builtin_core_vs_variables[i]);
   }

   generate_100ES_uniforms(instructions, state);

   generate_ARB_draw_buffers_variables(instructions, state, false,
				       vertex_shader);
}
