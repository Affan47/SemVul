get_directive(Kwv *kwv, char **value, char **errmsg)
{
  int i;
  char *v;
  Transform_directive d;

  kwv_set_mode(kwv, "+i-d");
  d = D_NONE;

  for (i = 0; directive_tab[i].name != NULL; i++) {
	if ((v = kwv_lookup_value(kwv, directive_tab[i].name)) != NULL) {
	  if (d != D_NONE) {
		if (errmsg != NULL)
		  *errmsg = "Only one directive is allowed";
		return(D_ERROR);
	  }
	  d = directive_tab[i].directive;
	  *value = v;
	}
  }

  return(d);
}
