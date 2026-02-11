cgraph_debug_gimple_stmt (struct function *this_cfun, gimple stmt)
{
  bool fndecl_was_null = false;

  if (cfun != this_cfun)
    set_cfun (this_cfun);

  if (!current_function_decl)
    {
      current_function_decl = this_cfun->decl;
      fndecl_was_null = true;
    }
  debug_gimple_stmt (stmt);
  if (fndecl_was_null)
    current_function_decl = NULL;
}
