yylex(void)
{
  extern YYSTYPE yylval;
  extern YYLTYPE yylloc;
  int result;
  int old_n;
  int is_elidable;
  int is_boiveho;

  if (!show_elisions) {

    TokenType tok;
    yylex1(&tok);
    yylval = tok.yylval;
    yylloc = tok.yylloc;
    return tok.value;
  }


  prev_token_was_pa_etc = cur_token_was_pa_etc;


  if (tokbuf.rp < tokbuf.n) {
    yylval = tokbuf.buf[tokbuf.rp].yylval;
    yylloc = tokbuf.buf[tokbuf.rp].yylloc;
    result = tokbuf.buf[tokbuf.rp].value;
    tokbuf.sp = tokbuf.rp;
    ++tokbuf.rp;
    return result;

  } else {
    tokbuf.rp = tokbuf.n = 0;
    do {
      if (tokbuf.n == tokbuf.max) {
        grow_buffer();
      }

      old_n = tokbuf.n;
      yylex1(&tokbuf.buf[tokbuf.n++]);

      tokbuf.flags[old_n].boiveho = 0;
      tokbuf.flags[old_n].subscript_before = 0;

      is_elidable = token_is_elidable(tokbuf.buf[old_n].yylval, &is_boiveho);
      tokbuf.flags[old_n].boiveho = is_boiveho;
      tokbuf.flags[old_n].tok_is_number_marker = token_is_number_marker(tokbuf.buf[old_n].yylval);
    } while (is_elidable);

    clear_conflicts();

#if 0
    fprintf(stderr, "refill gave %d tokens\n", tokbuf.n);
#endif

    yylval = tokbuf.buf[0].yylval;
    yylloc = tokbuf.buf[0].yylloc;
    result = tokbuf.buf[0].value;
    tokbuf.sp = tokbuf.rp;
    ++tokbuf.rp;

    if (tokbuf.rp == tokbuf.n) {

      switch (result) {
        case PA:
        case BU:
        case BY:
        case LAU:
        case TEI:
        case FOI:
          cur_token_was_pa_etc = 1;
          break;
        default:
          cur_token_was_pa_etc = 0;
          break;

      }
    }

    return result;

  }

}
