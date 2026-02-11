kwv_str(Kwv *kwv)
{
  unsigned int ui;
  char *p;
  Ds ds;
  Kwv_pair *pair;

  if (kwv == NULL)
	return(NULL);

  kwv->error_msg = NULL;
  if (kwv->npairs == 0)
	return("");

  ds_init(&ds);
  for (ui = 0; ui < kwv->nused; ui++) {
	pair = kwv->pairs[ui];
	while (pair != NULL) {
	  ds_asprintf(&ds, "%s=\"", pair->name);
	  for (p = pair->val; *p != '\0'; p++) {
		if (*p == '"') {
		  ds_concatc(&ds, '\\');
		  ds_concatc(&ds, '"');
		}
		else
		  ds_concatc(&ds, (int) *p);
	  }
	  ds_concatc(&ds, '"');
	  ds_concatc(&ds, '\n');
	  pair = pair->next;
	}
  }

  return(ds_buf(&ds));
}
