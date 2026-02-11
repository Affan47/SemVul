gftp_config_file_write_intcombo (gftp_config_vars * cv, char *buf,
                                 size_t buflen, int to_config_file)
{
  char **clist;

  clist = cv->listdata;
  if (clist != NULL)
    g_snprintf (buf, buflen, "%s", clist[GPOINTER_TO_INT(cv->value)]);
  else
    g_snprintf (buf, buflen, _("<unknown>"));

  return (0);
}
