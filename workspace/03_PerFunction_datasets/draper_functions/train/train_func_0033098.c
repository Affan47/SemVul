acl_parse_name_el(char *el, char **name, unsigned int *suffix)
{
  char *dotp, *p, *q;
  Acl_status st;

  p = strdup(el);
  if ((q = strprefix(p, ACL_DISABLED_NAME_PREFIX)) != NULL) {
	st = ACL_STATUS_DISABLED;
	p = q;
  }
  else {
	st = ACL_STATUS_ENABLED;
  }

  if ((q = strprefix(p, ACL_NAME_PREFIX)) == NULL)
	return(ACL_STATUS_ERROR);
  p = q;

  if ((dotp = strrchr(p, (int) '.')) == NULL)
	return(ACL_STATUS_ERROR);
  *dotp = '\0';
  q = dotp + 1;

  if (name != NULL)
	*name = p;

  if (suffix != NULL) {
	if (strnum(q, STRNUM_UI, suffix) == -1)
	  return(ACL_STATUS_ERROR);
  }

  return(st);
}
