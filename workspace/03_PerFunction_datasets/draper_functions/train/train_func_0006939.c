lookup_name_cmp(char *str)
{
  DACS_name_cmp cmp_mode;

  if (str == NULL)
	cmp_mode = name_cmp_mode_default;
  else if (strcaseeq(str, "case"))
	cmp_mode = DACS_NAME_CMP_CASE;
  else if (strcaseeq(str, "nocase"))
	cmp_mode = DACS_NAME_CMP_NOCASE;
  else if (strcaseeq(str, "default"))
	cmp_mode = name_cmp_mode_default;
  else
	cmp_mode = DACS_NAME_CMP_UNKNOWN;

  return(cmp_mode);
}
