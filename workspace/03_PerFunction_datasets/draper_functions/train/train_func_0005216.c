conf_auth_vartab_by_id(char *auth_id)
{
  int i;
  Kwv_vartab *found, *id, *tab;

  i = 0;
  found = NULL;
  while ((tab = conf_auth_vartab(i++)) != NULL) {
	if ((id = kwv_vartab_lookup(tab, "AUTH_ID")) != NULL
		&& id->pair != NULL && id->pair->val != NULL
		&& streq(id->pair->val, auth_id)) {

	  if (found != NULL)
		return(NULL);
	  found = tab;
	}
  }

  return(found);
}
