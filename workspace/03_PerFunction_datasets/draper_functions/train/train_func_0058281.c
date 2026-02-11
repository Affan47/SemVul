read(exec_list *instructions, const char *src, bool scan_for_protos)
{
   void *sx_mem_ctx = ralloc_context(NULL);
   s_expression *expr = s_expression::read_expression(sx_mem_ctx, src);
   if (expr == NULL) {
      ir_read_error(NULL, "couldn't parse S-Expression.");
      return;
   }

   if (scan_for_protos) {
      scan_for_prototypes(instructions, expr);
      if (state->error)
	 return;
   }

   read_instructions(instructions, expr, NULL);
   ralloc_free(sx_mem_ctx);

   if (debug)
      validate_ir_tree(instructions);
}
