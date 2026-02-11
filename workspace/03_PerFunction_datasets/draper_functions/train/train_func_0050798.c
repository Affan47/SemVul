moblin_netbook_rc_style_parse (GtkRcStyle  *rc_style,
                               GtkSettings *settings,
                               GScanner    *scanner)
{
  GTokenType token;
  static GQuark scope_id;
  guint old_scope;
  int i;
  MoblinNetbookRcStyle *mb_style = MOBLIN_NETBOOK_RC_STYLE (rc_style);

  if (!scope_id)
    scope_id = g_quark_from_string ("moblin-gtk-engine");


  old_scope = g_scanner_set_scope (scanner, scope_id);


  if (!g_scanner_lookup_symbol (scanner, moblin_rc_symbols[0].name))
    {
      for (i = 0; moblin_rc_symbols[i].name; i++)
        {
          g_scanner_scope_add_symbol (scanner,
                                      scope_id,
                                      moblin_rc_symbols[i].name,
                                      GINT_TO_POINTER (moblin_rc_symbols[i].
                                                       token));
        }
    }

  token = g_scanner_peek_next_token (scanner);
  while (token != G_TOKEN_RIGHT_CURLY)
    {
      switch (token)
        {
        case TOKEN_BORDER_COLOR:
          token = moblin_parse_border_color (scanner, mb_style);
          break;

        case TOKEN_RADIUS:
          g_scanner_get_next_token (scanner);

          token = moblin_get_token (scanner, G_TOKEN_EQUAL_SIGN);
          if (token != G_TOKEN_NONE)
            break;

          token = moblin_get_token (scanner, G_TOKEN_INT);
          if (token != G_TOKEN_NONE)
            break;

          mb_style->radius = scanner->value.v_int;
          break;

        case TOKEN_SHADOW:
          g_scanner_get_next_token (scanner);

          token = moblin_get_token (scanner, G_TOKEN_EQUAL_SIGN);
          if (token != G_TOKEN_NONE)
            break;

          token = moblin_get_token (scanner, G_TOKEN_FLOAT);
          if (token != G_TOKEN_NONE)
            break;

          mb_style->shadow = scanner->value.v_float;
          mb_style->shadow_set = TRUE;
          break;

        default:
          g_scanner_get_next_token (scanner);
          token = G_TOKEN_RIGHT_CURLY;
          break;

        }

      if (token != G_TOKEN_NONE)
        {
          return token;
        }

      token = g_scanner_peek_next_token (scanner);
    }

  g_scanner_get_next_token (scanner);
  g_scanner_set_scope (scanner, old_scope);
  return G_TOKEN_NONE;
}
