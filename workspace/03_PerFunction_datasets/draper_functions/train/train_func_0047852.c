cp_parser_objc_selector (cp_parser* parser)
{
  cp_token *token = cp_lexer_consume_token (parser->lexer);

  if (!cp_parser_objc_selector_p (token->type))
    {
      error_at (token->location, "invalid Objective-C++ selector name");
      return error_mark_node;
    }


  switch (token->type)
    {
    case CPP_AND_AND: return get_identifier ("and");
    case CPP_AND_EQ: return get_identifier ("and_eq");
    case CPP_AND: return get_identifier ("bitand");
    case CPP_OR: return get_identifier ("bitor");
    case CPP_COMPL: return get_identifier ("compl");
    case CPP_NOT: return get_identifier ("not");
    case CPP_NOT_EQ: return get_identifier ("not_eq");
    case CPP_OR_OR: return get_identifier ("or");
    case CPP_OR_EQ: return get_identifier ("or_eq");
    case CPP_XOR: return get_identifier ("xor");
    case CPP_XOR_EQ: return get_identifier ("xor_eq");
    default: return token->u.value;
    }
}
