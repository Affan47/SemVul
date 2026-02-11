ident_username(Credentials *cr)
{
  Ds ds;

  ds_init(&ds);
  if (cr->federation != NULL)
	ds_asprintf(&ds, "%s%c%c", cr->federation,
				JURISDICTION_NAME_SEP_CHAR, JURISDICTION_NAME_SEP_CHAR);
  if (cr->home_jurisdiction != NULL)
	ds_asprintf(&ds, "%s%c",
				cr->home_jurisdiction, JURISDICTION_NAME_SEP_CHAR);
  ds_asprintf(&ds, "%s", cr->username);

  return(ds_buf(&ds));
}
