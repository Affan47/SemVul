compile_shader(struct gl_context *ctx, struct gl_shader *shader)
{
   struct _mesa_glsl_parse_state *state =
      new(shader) _mesa_glsl_parse_state(ctx, shader->Type, shader);

   const char *source = shader->Source;
   state->error = preprocess(state, &source, &state->info_log,
			     state->extensions, ctx->API) != 0;

   if (!state->error) {
      _mesa_glsl_lexer_ctor(state, source);
      _mesa_glsl_parse(state);
      _mesa_glsl_lexer_dtor(state);
   }

   if (dump_ast) {
      foreach_list_const(n, &state->translation_unit) {
	 ast_node *ast = exec_node_data(ast_node, n, link);
	 ast->print();
      }
      printf("\n\n");
   }

   shader->ir = new(shader) exec_list;
   if (!state->error && !state->translation_unit.is_empty())
      _mesa_ast_to_hir(shader->ir, state);


   if (!state->error && dump_hir) {
      validate_ir_tree(shader->ir);
      _mesa_print_ir(shader->ir, state);
   }


   if (!state->error && !shader->ir->is_empty()) {
      bool progress;
      do {
	 progress = do_common_optimization(shader->ir, false, 32);
      } while (progress);

      validate_ir_tree(shader->ir);
   }


   if (!state->error && dump_lir) {
      _mesa_print_ir(shader->ir, state);
   }

   shader->symbols = state->symbols;
   shader->CompileStatus = !state->error;
   shader->Version = state->language_version;
   memcpy(shader->builtins_to_link, state->builtins_to_link,
	  sizeof(shader->builtins_to_link[0]) * state->num_builtins_to_link);
   shader->num_builtins_to_link = state->num_builtins_to_link;

   if (shader->InfoLog)
      ralloc_free(shader->InfoLog);

   shader->InfoLog = state->info_log;


   reparent_ir(shader->ir, shader);

   ralloc_free(state);

   return;
}
