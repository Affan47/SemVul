gegl_color_set_from_string (GeglColor   *self,
                            const gchar *color_string)
{
  GScanner         *scanner;
  GTokenType        token_type;
  GTokenValue       token_value;
  gboolean          color_parsing_successfull;

  scanner                               = g_scanner_new (NULL);
  scanner->config->cpair_comment_single = "";
  g_scanner_input_text (scanner, color_string, strlen (color_string));

  token_type  = g_scanner_get_next_token (scanner);
  token_value = g_scanner_cur_value (scanner);

  if (token_type == G_TOKEN_IDENTIFIER &&
      g_ascii_strcasecmp (token_value.v_identifier, "rgb") == 0)
    {
      color_parsing_successfull = parse_float_argument_list (self, scanner, 3);
      self->priv->rgba_color[3]       = 1.f;
    }
  else if (token_type == G_TOKEN_IDENTIFIER &&
           g_ascii_strcasecmp (token_value.v_identifier, "rgba") == 0)
    {
      color_parsing_successfull = parse_float_argument_list (self, scanner, 4);
    }
  else if (token_type == '#')
    {
      color_parsing_successfull = parse_hex (self, color_string);
    }
  else if (token_type == G_TOKEN_IDENTIFIER)
    {
      color_parsing_successfull = parse_color_name (self, color_string);
    }
  else
    {
      color_parsing_successfull = FALSE;
    }

  if (!color_parsing_successfull)
    {
      memcpy (self->priv->rgba_color,
              parsing_error_color,
              sizeof (parsing_error_color));
      g_warning ("Parsing of color string \"%s\" into GeglColor failed! "
                 "Using transparent cyan instead",
                 color_string);
    }

  g_scanner_destroy (scanner);
}
