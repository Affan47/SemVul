_validateHeader(const gchar *filename, int kind)
{
  FILE *file;
  float version;
  char *msg, *header;
  char line[TOOL_MAX_LINE_LENGTH];

  DBG_fprintf(stderr, "Visu ConfigFile: looking for header of \n  '%s' ... ", filename);
  if (strstr(filename, ".xml"))
    {
      DBG_fprintf(stderr, "accepted.\n");
      return TRUE;
    }

  file = fopen(filename, "r");
  if (!file)
    {
      g_warning("The file '%s' should be readable but something goes"
                " nasty when one wants to open it.\n", filename);
      return FALSE;
    }
  version = 0.;
  msg = fgets(line, TOOL_MAX_LINE_LENGTH, file);
  fclose(file);
  if (kind == VISU_CONFIG_FILE_RESOURCE)
    header = RESOURCE_HEADER;
  else
    header = PARAMETER_HEADER;
  if (msg && !strncmp(line, header, strlen(header))
      && sscanf(line + strlen(header) + 2, "%f", &version))
    if (version >= 3.)
      {
        DBG_fprintf(stderr, "ok.\n");
        return TRUE;
      }
  DBG_fprintf(stderr, "wrong.\n");
  return FALSE;
}
