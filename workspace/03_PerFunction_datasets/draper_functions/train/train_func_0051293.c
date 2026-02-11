c_parser_objc_maybe_method_attributes (c_parser* parser, tree* attributes)
{
  bool bad = false;
  if (*attributes)
    {
      c_parser_error (parser,
		    "method attributes must be specified at the end only");
      *attributes = NULL_TREE;
      bad = true;
    }

  if (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
    *attributes = c_parser_attributes (parser);


  if (*attributes == NULL_TREE || bad)
    return bad;


  if (c_parser_next_token_is (parser, CPP_SEMICOLON)
      || c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    return bad;


  c_parser_error (parser,
		  "expected %<;%> or %<{%> after method attribute definition");
  return true;
}
