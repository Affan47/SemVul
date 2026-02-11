hir(exec_list *instructions,
			     struct _mesa_glsl_parse_state *state)
{
   foreach_list_typed (ast_case_statement, case_stmt, link, & this->cases)
      case_stmt->hir(instructions, state);


   return NULL;
}
