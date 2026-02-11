set_dollar_vars_changed ()
{
  if (variable_context)
    changed_dollar_vars |= ARGS_FUNC;
  else if (this_shell_builtin == set_builtin)
    changed_dollar_vars |= ARGS_SETBLTIN;
  else
    changed_dollar_vars |= ARGS_INVOC;
}
