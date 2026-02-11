aurora_rc_style_parse (GtkRcStyle *rc_style,
			   GtkSettings  *settings,
			   GScanner   *scanner)

{
  static GQuark scope_id = 0;
  AuroraRcStyle *aurora_style = AURORA_RC_STYLE (rc_style);

  guint old_scope;
  guint token;


  if (!scope_id)
    scope_id = g_quark_from_string("aurora_theme_engine");


  old_scope = g_scanner_set_scope(scanner, scope_id);


	if (!g_scanner_lookup_symbol(scanner, aurora_rc_symbols)) {
		gchar *current_symbol = aurora_rc_symbols;
		gint i = G_TOKEN_LAST + 1;


		while ((current_symbol[0] != '\0') && (i < TOKEN_LAST)) {
			g_scanner_scope_add_symbol(scanner, scope_id, current_symbol, GINT_TO_POINTER (i));

			current_symbol += strlen(current_symbol) + 1;
			i++;
		}
		g_assert (i == TOKEN_LAST && current_symbol[0] == '\0');
	}


  token = g_scanner_peek_next_token(scanner);
  while (token != G_TOKEN_RIGHT_CURLY)
    {
      switch (token)
	{
	case TOKEN_CONTRAST:
	  token = theme_parse_double (settings, scanner, &aurora_style->contrast);
	  aurora_style->flags |= AUR_FLAG_CONTRAST;
	  break;
	case TOKEN_MENUBARSTYLE:
	  token = theme_parse_int (settings, scanner, &aurora_style->menubarstyle);
	  aurora_style->flags |= AUR_FLAG_MENUBARSTYLE;
	  break;
	case TOKEN_CURVATURE:
	  token = theme_parse_double (settings, scanner, &aurora_style->curvature);
	  aurora_style->flags |= AUR_FLAG_CURVATURE;
	  break;
	case TOKEN_ANIMATION:
	  token = theme_parse_boolean (settings, scanner, &aurora_style->animation);
	  aurora_style->flags |= AUR_FLAG_ANIMATION;
	  break;
	case TOKEN_OLD_ARROWSTYLE:
	  token = theme_parse_boolean (settings, scanner, &aurora_style->old_arrowstyle);
	  aurora_style->flags |= AUR_FLAG_OLD_ARROWSTYLE;
	  break;
	case TOKEN_ARROWSIZE:
	  token = theme_parse_double (settings, scanner, &aurora_style->arrowsize);
	  aurora_style->flags |= AUR_FLAG_ARROWSTYLE;
	  break;
	default:
	  g_scanner_get_next_token(scanner);
	  token = G_TOKEN_RIGHT_CURLY;
	  break;
	}

      if (token != G_TOKEN_NONE)
	return token;

      token = g_scanner_peek_next_token(scanner);
    }

  g_scanner_get_next_token(scanner);

  g_scanner_set_scope(scanner, old_scope);

  return G_TOKEN_NONE;
}
