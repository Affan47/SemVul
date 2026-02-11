c_parser_compound_statement (c_parser *parser)
{
  tree stmt;
  location_t brace_loc;
  brace_loc = c_parser_peek_token (parser)->location;
  if (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    {


      stmt = c_begin_compound_stmt (true);
      c_end_compound_stmt (brace_loc, stmt, true);
      return error_mark_node;
    }
  stmt = c_begin_compound_stmt (true);
  c_parser_compound_statement_nostart (parser);
  return c_end_compound_stmt (brace_loc, stmt, true);
}
