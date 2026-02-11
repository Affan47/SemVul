theme_parse_color(GtkSettings  *settings,
		  GScanner     *scanner,
		  GdkColor     *color)
{
  guint token;


  token = g_scanner_get_next_token(scanner);

  token = g_scanner_get_next_token(scanner);
  if (token != G_TOKEN_EQUAL_SIGN)
    return G_TOKEN_EQUAL_SIGN;

  return gtk_rc_parse_color (scanner, color);
}
