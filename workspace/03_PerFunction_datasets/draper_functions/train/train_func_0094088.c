yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, parser_helper_t *ctx)
{
  YYUSE (yyvaluep);
  YYUSE (ctx);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  switch (yytype)
    {
          case 3:
#line 90 "settings/settings_parser.y"
      { free(((*yyvaluep).s)); }
#line 1028 "settings/settings_parser.c"
        break;

    case 4:
#line 90 "settings/settings_parser.y"
      { free(((*yyvaluep).s)); }
#line 1034 "settings/settings_parser.c"
        break;

    case 12:
#line 92 "settings/settings_parser.y"
      { pop_section(ctx); settings_section_destroy(((*yyvaluep).sec), NULL); }
#line 1040 "settings/settings_parser.c"
        break;

    case 13:
#line 92 "settings/settings_parser.y"
      { pop_section(ctx); settings_section_destroy(((*yyvaluep).sec), NULL); }
#line 1046 "settings/settings_parser.c"
        break;

    case 14:
#line 93 "settings/settings_parser.y"
      { settings_kv_destroy(((*yyvaluep).kv), NULL); }
#line 1052 "settings/settings_parser.c"
        break;

    case 15:
#line 90 "settings/settings_parser.y"
      { free(((*yyvaluep).s)); }
#line 1058 "settings/settings_parser.c"
        break;

    case 16:
#line 90 "settings/settings_parser.y"
      { free(((*yyvaluep).s)); }
#line 1064 "settings/settings_parser.c"
        break;


      default:
        break;
    }
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}
