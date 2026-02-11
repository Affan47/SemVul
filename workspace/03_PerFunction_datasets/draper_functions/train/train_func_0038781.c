error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }
