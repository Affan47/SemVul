cp_lexer_print_token (FILE * stream, cp_token *token)
{


  static const char *const token_names[] = {

#define OP(e, s) #e,
#define TK(e, s) #e,
    TTYPE_TABLE
#undef OP
#undef TK

    "KEYWORD",
    "TEMPLATE_ID",
    "NESTED_NAME_SPECIFIER",
  };


  switch (token->type)
    {
    case CPP_KEYWORD:


      if (TREE_CODE (token->u.value) != IDENTIFIER_NODE)
	break;

    case CPP_NAME:
      fputs (IDENTIFIER_POINTER (token->u.value), stream);
      break;

    case CPP_STRING:
    case CPP_STRING16:
    case CPP_STRING32:
    case CPP_WSTRING:
    case CPP_UTF8STRING:
      fprintf (stream, " \"%s\"", TREE_STRING_POINTER (token->u.value));
      break;

    case CPP_NUMBER:
      print_generic_expr (stream, token->u.value, 0);
      break;

    default:


      if (token->type < ARRAY_SIZE(token_names))
	fputs (token_names[token->type], stream);
      else
	fprintf (stream, "[%d]", token->type);
      break;
    }
}
