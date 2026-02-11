location_increment(Dynare::parser::location_type *yylloc, const char *yytext)
{
  while (*yytext != 0)
    if (*yytext++ == '\n')
      yylloc->lines(1);
    else
      yylloc->columns(1);
}
