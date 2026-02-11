debug_dump_variable (sc_gameref_t game, sc_int variable)
{
  const sc_prop_setref_t bundle = gs_get_bundle (game);
  const sc_var_setref_t vars = gs_get_vars (game);
  sc_vartype_t vt_key[3], vt_rvalue;
  const sc_char *name;
  sc_int var_type;

  debug_print_variable (game, variable);
  if_print_debug_character ('\n');

  vt_key[0].string = "Variables";
  vt_key[1].integer = variable;
  vt_key[2].string = "Name";
  name = prop_get_string (bundle, "S<-sis", vt_key);

  if_print_debug ("    Value = ");
  if (var_get (vars, name, &var_type, &vt_rvalue))
    {
      switch (var_type)
        {
        case VAR_INTEGER:
          {
            sc_char buffer[32];

            sprintf (buffer, "%ld", vt_rvalue.integer);
            if_print_debug (buffer);
            break;
          }
        case VAR_STRING:
          debug_print_quoted (vt_rvalue.string);
          break;
        default:
          if_print_debug ("[Unknown]");
          break;
        }
    }
  else
    if_print_debug ("[Unknown]");
  if_print_debug_character ('\n');
}
