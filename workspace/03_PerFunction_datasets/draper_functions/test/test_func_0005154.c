debug_print_object (sc_gameref_t game, sc_int object)
{
  const sc_prop_setref_t bundle = gs_get_bundle (game);
  sc_vartype_t vt_key[3];
  sc_bool bstatic;
  sc_char buffer[32];
  const sc_char *prefix, *name;

  if (object < 0 || object >= gs_object_count (game))
    {
      if_print_debug ("Object ");
      sprintf (buffer, "%ld ", object);
      if_print_debug (buffer);
      if_print_debug ("[Out of range]");
      return;
    }

  vt_key[0].string = "Objects";
  vt_key[1].integer = object;
  vt_key[2].string = "Static";
  bstatic = prop_get_boolean (bundle, "B<-sis", vt_key);
  vt_key[2].string = "Prefix";
  prefix = prop_get_string (bundle, "S<-sis", vt_key);
  vt_key[2].string = "Short";
  name = prop_get_string (bundle, "S<-sis", vt_key);
  if (bstatic)
    if_print_debug ("Static ");
  else
    if_print_debug ("Dynamic ");
  sprintf (buffer, "%ld ", object);
  if_print_debug (buffer);
  debug_print_quoted (prefix);
  if_print_debug_character (' ');
  debug_print_quoted (name);
}
