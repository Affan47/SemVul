get_function_decl(ClassBrowserFunction *function)
{
  GString *function_decl;
  function_decl = g_string_new(function->functionname);
    if (function->paramlist) {
      g_string_append_printf(function_decl, "(%s)", function->paramlist);
    } else {
      function_decl = g_string_append(function_decl, "()");
    }
  return function_decl;
}
