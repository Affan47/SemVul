yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, Node **root, const char *text)
{
  YYUSE (yyvaluep);
  YYUSE (root);
  YYUSE (text);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  switch (yytype)
    {
          case 16:
#line 74 "parse.y"
      { ((*yyvaluep).node)->release(); }
#line 1023 "parse.cc"
        break;

    case 17:
#line 74 "parse.y"
      { ((*yyvaluep).node)->release(); }
#line 1029 "parse.cc"
        break;

    case 18:
#line 74 "parse.y"
      { ((*yyvaluep).node)->release(); }
#line 1035 "parse.cc"
        break;

    case 19:
#line 74 "parse.y"
      { ((*yyvaluep).node)->release(); }
#line 1041 "parse.cc"
        break;

    case 20:
#line 74 "parse.y"
      { ((*yyvaluep).node)->release(); }
#line 1047 "parse.cc"
        break;


      default:
        break;
    }
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}
