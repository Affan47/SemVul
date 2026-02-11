flag_instrument_functions_exclude_p (tree fndecl)
{
  vec<char_p> *v;

  v = (vec<char_p> *) flag_instrument_functions_exclude_functions;
  if (v && v->length () > 0)
    {
      const char *name;
      int i;
      char *s;

      name = lang_hooks.decl_printable_name (fndecl, 0);
      FOR_EACH_VEC_ELT (*v, i, s)
	if (strstr (name, s) != NULL)
	  return true;
    }

  v = (vec<char_p> *) flag_instrument_functions_exclude_files;
  if (v && v->length () > 0)
    {
      const char *name;
      int i;
      char *s;

      name = DECL_SOURCE_FILE (fndecl);
      FOR_EACH_VEC_ELT (*v, i, s)
	if (strstr (name, s) != NULL)
	  return true;
    }

  return false;
}
