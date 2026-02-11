pop_function_context (void)
{
  struct function *p = VEC_pop (function_p, function_context_stack);
  set_cfun (p);
  current_function_decl = p->decl;


  virtuals_instantiated = 0;
  generating_concat_p = 1;
}
