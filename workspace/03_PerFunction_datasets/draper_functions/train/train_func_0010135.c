css_parse_simple_selector (GScanner      *scanner,
                           MxSelector    *selector)
{
  guint token;
  gchar *tmp;


  token = g_scanner_peek_next_token (scanner);
  switch (token)
    {
    case '*':
      g_scanner_get_next_token (scanner);
      selector->type = g_strdup ("*");
      break;
    case G_TOKEN_IDENTIFIER:
      g_scanner_get_next_token (scanner);
      selector->type = g_strdup (scanner->value.v_identifier);
      break;
    default:
      break;
    }


  token = g_scanner_peek_next_token (scanner);
  while (token != G_TOKEN_NONE)
    {
      switch (token)
        {

        case '#':
          g_scanner_get_next_token (scanner);
          token = g_scanner_get_next_token (scanner);
          if (token != G_TOKEN_IDENTIFIER)
            return G_TOKEN_IDENTIFIER;
          selector->id = g_strdup (scanner->value.v_identifier);
          break;

        case '.':
          g_scanner_get_next_token (scanner);
          token = g_scanner_get_next_token (scanner);
          if (token != G_TOKEN_IDENTIFIER)
            return G_TOKEN_IDENTIFIER;
          selector->class = g_strdup (scanner->value.v_identifier);
          break;

        case ':':
          g_scanner_get_next_token (scanner);
          token = g_scanner_get_next_token (scanner);
          if (token != G_TOKEN_IDENTIFIER)
            return G_TOKEN_IDENTIFIER;

          tmp = selector->pseudo_class;

          if (selector->pseudo_class)
            selector->pseudo_class = g_strconcat (selector->pseudo_class, ":",
                                                  scanner->value.v_identifier,
                                                  NULL);
          else
            selector->pseudo_class = g_strdup (scanner->value.v_identifier);

          g_free (tmp);

          break;


        default:
          return G_TOKEN_NONE;
          break;
        }
      token = g_scanner_peek_next_token (scanner);
    }
  return G_TOKEN_NONE;
}
