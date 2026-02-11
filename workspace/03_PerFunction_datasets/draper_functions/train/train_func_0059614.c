gegl_param_string_validate (GParamSpec *pspec,
                            GValue     *value)
{
  GeglParamSpecString *sspec  = GEGL_PARAM_SPEC_STRING (pspec);
  gchar               *string = value->data[0].v_pointer;

  if (string)
    {
      gchar *s;

      if (!sspec->no_validate &&
          !g_utf8_validate (string, -1, (const gchar **) &s))
        {
          for (; *s; s++)
            if (*s < ' ')
              *s = '?';

          return TRUE;
        }
    }
  else if (!sspec->null_ok)
    {
      value->data[0].v_pointer = g_strdup ("");
      return TRUE;
    }

  return FALSE;
}
