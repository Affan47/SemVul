debug_print_variable (sc_gameref_t game, sc_int variable)
{
  const sc_prop_setref_t bundle = gs_get_bundle (game);
  const sc_var_setref_t vars = gs_get_vars (game);
  sc_vartype_t vt_key[3], vt_rvalue;
  sc_char buffer[32];
  sc_int var_type;
  const sc_char *name;

  if (variable < 0 || variable >= debug_variable_count (game))
    {
      if_print_debug ("Variable ");
      sprintf (buffer, "%ld ", variable);
      if_print_debug (buffer);
      if_print_debug ("[Out of range]");
      return;
    }

  vt_key[0].string = "Variables";
  vt_key[1].integer = variable;
  vt_key[2].string = "Name";
  name = prop_get_string (bundle, "S<-sis", vt_key);

  if (var_get (vars, name, &var_type, &vt_rvalue))
    {
      switch (var_type)
        {
        case VAR_INTEGER:
          if_print_debug ("Integer ");
          break;
        case VAR_STRING:
          if_print_debug ("String ");
          break;
        default:
          if_print_debug ("[Invalid type] ");
          break;
        }
    }
  else
    if_print_debug ("[Invalid variable] ");
  sprintf (buffer, "%ld ", variable);
  if_print_debug (buffer);
  debug_print_quoted (name);
}
