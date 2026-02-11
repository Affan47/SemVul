parse_positive_integer (const char          *str,
                        int                 *val,
                        GMarkupParseContext *context,
                        MetaTheme           *theme,
                        GError             **error)
{
  char *end;
  long l;
  int j;

  *val = 0;

  end = NULL;


  if (META_THEME_ALLOWS (theme, META_THEME_UBIQUITOUS_CONSTANTS) &&
      meta_theme_lookup_int_constant (theme, str, &j))
    {

      l = j;
    }
  else
    {


      l = strtol (str, &end, 10);

      if (end == NULL || end == str)
      {
        set_error (error, context, G_MARKUP_ERROR,
                   G_MARKUP_ERROR_PARSE,
                   _("Could not parse \"%s\" as an integer"),
                   str);
        return FALSE;
      }

    if (*end != '\0')
      {
        set_error (error, context, G_MARKUP_ERROR,
                   G_MARKUP_ERROR_PARSE,
                   _("Did not understand trailing characters \"%s\" in string \"%s\""),
                   end, str);
        return FALSE;
      }
    }

  if (l < 0)
    {
      set_error (error, context, G_MARKUP_ERROR,
                 G_MARKUP_ERROR_PARSE,
                 _("Integer %ld must be positive"), l);
      return FALSE;
    }

  if (l > MAX_REASONABLE)
    {
      set_error (error, context, G_MARKUP_ERROR,
                 G_MARKUP_ERROR_PARSE,
                 _("Integer %ld is too large, current max is %d"),
                 l, MAX_REASONABLE);
      return FALSE;
    }

  *val = (int) l;

  return TRUE;
}
