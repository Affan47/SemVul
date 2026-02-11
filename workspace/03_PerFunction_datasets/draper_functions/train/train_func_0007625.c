check_macro_name (symname, assertion)
     U_CHAR *symname;
     int assertion;
{
  U_CHAR *p;
  int sym_length;

  for (p = symname; is_idchar[*p]; p++)
    ;
  sym_length = p - symname;
  if (sym_length == 0
      || (sym_length == 1 && *symname == 'L' && (*p == '\'' || *p == '"')))
    error (assertion ? "invalid assertion name" : "invalid macro name");
  else if (!is_idstart[*symname]
	   || (sym_length == 7 && ! bcmp (symname, "defined", 7)))
    error ((assertion
	    ? "invalid assertion name `%.*s'"
	    : "invalid macro name `%.*s'"),
	   sym_length, symname);
  return sym_length;
}
