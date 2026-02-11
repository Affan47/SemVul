check_header_entry (const message_ty *mp, const char *msgstr_string)
{
  static const char *required_fields[] =
  {
    "Project-Id-Version", "PO-Revision-Date", "Last-Translator",
    "Language-Team", "MIME-Version", "Content-Type",
    "Content-Transfer-Encoding",

    "Language"
  };
  static const char *default_values[] =
  {
    "PACKAGE VERSION", "YEAR-MO-DA", "FULL NAME", "LANGUAGE", NULL,
    "text/plain; charset=CHARSET", "ENCODING",
    ""
  };
  const size_t nfields = SIZEOF (required_fields);
  const size_t nrequiredfields = nfields - 1;
  int cnt;

  for (cnt = 0; cnt < nfields; ++cnt)
    {
      int severity =
        (cnt < nrequiredfields ? PO_SEVERITY_ERROR : PO_SEVERITY_WARNING);
      const char *field = required_fields[cnt];
      size_t len = strlen (field);
      const char *line;

      for (line = msgstr_string; *line != '\0'; )
        {
          if (strncmp (line, field, len) == 0 && line[len] == ':')
            {
              const char *p = line + len + 1;


              if (*p == ' ')
                p++;
              if (default_values[cnt] != NULL
                  && strncmp (p, default_values[cnt],
                              strlen (default_values[cnt])) == 0)
                {
                  p += strlen (default_values[cnt]);
                  if (*p == '\0' || *p == '\n')
                    {
		      char *msg =
			xasprintf (_("header field '%s' still has the initial default value\n"),
				   field);
		      po_xerror (severity, mp, NULL, 0, 0, true, msg);
		      free (msg);
                    }
                }
              break;
            }
          line = strchrnul (line, '\n');
          if (*line == '\n')
            line++;
        }
      if (*line == '\0')
        {
          char *msg =
            xasprintf (_("header field '%s' missing in header\n"),
                       field);
          po_xerror (severity, mp, NULL, 0, 0, true, msg);
          free (msg);
        }
    }
}
