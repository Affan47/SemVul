pysol_config_txt_parse_line_0 (PySolConfigTxtData *data,
                               const char *line)
{
  char **fields;
  gsize n_fields;
  gboolean retval = FALSE;


  data->version = 0;
  data->n_cards = 52;
  data->type = 1;

  fields = g_strsplit (line, ";", -1);
  if (!fields)
    return FALSE;

  n_fields = g_strv_length (fields);
  if (n_fields < 2)
    goto out;
  if (strcmp (g_strstrip (fields[0]), "PySol solitaire cardset") != 0 &&
      strcmp (g_strstrip (fields[0]), "PySolFC solitaire cardset") != 0)
    goto out;
  if (!parse_int (g_strstrip (fields[1]), &data->version))
    goto out;

  if (data->version >= 3) {
    if (n_fields < 4)
      goto out;

    if (strlen (fields[2]) > 0)
      data->ext = g_strstrip (g_strdup (fields[2]));
    else
      data->ext = g_strdup (".gif");

    if (!parse_int (fields[3], &data->type))
      goto out;
    if (!parse_int (fields[4], &data->n_cards))
      goto out;
  }

  retval = TRUE;
out:
  g_strfreev (fields);
  return retval;
}
