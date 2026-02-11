stab_demangle_function_name (struct stab_demangle_info *minfo,
			     const char **pp, const char *scan)
{
  const char *name;


  name = *pp;
  *pp = scan + 2;

  if (*pp - name >= 5
	   && CONST_STRNEQ (name, "type")
	   && (name[4] == '$' || name[4] == '.'))
    {
      const char *tem;


      tem = name + 5;
      if (! stab_demangle_type (minfo, &tem, (debug_type *) NULL))
	return FALSE;
    }
  else if (name[0] == '_'
	   && name[1] == '_'
	   && name[2] == 'o'
	   && name[3] == 'p')
    {
      const char *tem;


      tem = name + 4;
      if (! stab_demangle_type (minfo, &tem, (debug_type *) NULL))
	return FALSE;
    }

  return TRUE;
}
