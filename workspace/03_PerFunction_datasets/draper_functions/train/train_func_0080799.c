cp_parser_trait_expr (cp_parser* parser, enum rid keyword)
{
  cp_trait_kind kind;
  tree type1, type2 = NULL_TREE;
  bool binary = false;
  cp_decl_specifier_seq decl_specs;

  switch (keyword)
    {
    case RID_HAS_NOTHROW_ASSIGN:
      kind = CPTK_HAS_NOTHROW_ASSIGN;
      break;
    case RID_HAS_NOTHROW_CONSTRUCTOR:
      kind = CPTK_HAS_NOTHROW_CONSTRUCTOR;
      break;
    case RID_HAS_NOTHROW_COPY:
      kind = CPTK_HAS_NOTHROW_COPY;
      break;
    case RID_HAS_TRIVIAL_ASSIGN:
      kind = CPTK_HAS_TRIVIAL_ASSIGN;
      break;
    case RID_HAS_TRIVIAL_CONSTRUCTOR:
      kind = CPTK_HAS_TRIVIAL_CONSTRUCTOR;
      break;
    case RID_HAS_TRIVIAL_COPY:
      kind = CPTK_HAS_TRIVIAL_COPY;
      break;
    case RID_HAS_TRIVIAL_DESTRUCTOR:
      kind = CPTK_HAS_TRIVIAL_DESTRUCTOR;
      break;
    case RID_HAS_VIRTUAL_DESTRUCTOR:
      kind = CPTK_HAS_VIRTUAL_DESTRUCTOR;
      break;
    case RID_IS_ABSTRACT:
      kind = CPTK_IS_ABSTRACT;
      break;
    case RID_IS_BASE_OF:
      kind = CPTK_IS_BASE_OF;
      binary = true;
      break;
    case RID_IS_CLASS:
      kind = CPTK_IS_CLASS;
      break;
    case RID_IS_CONVERTIBLE_TO:
      kind = CPTK_IS_CONVERTIBLE_TO;
      binary = true;
      break;
    case RID_IS_EMPTY:
      kind = CPTK_IS_EMPTY;
      break;
    case RID_IS_ENUM:
      kind = CPTK_IS_ENUM;
      break;
    case RID_IS_FINAL:
      kind = CPTK_IS_FINAL;
      break;
    case RID_IS_LITERAL_TYPE:
      kind = CPTK_IS_LITERAL_TYPE;
      break;
    case RID_IS_POD:
      kind = CPTK_IS_POD;
      break;
    case RID_IS_POLYMORPHIC:
      kind = CPTK_IS_POLYMORPHIC;
      break;
    case RID_IS_STD_LAYOUT:
      kind = CPTK_IS_STD_LAYOUT;
      break;
    case RID_IS_TRIVIAL:
      kind = CPTK_IS_TRIVIAL;
      break;
    case RID_IS_UNION:
      kind = CPTK_IS_UNION;
      break;
    case RID_UNDERLYING_TYPE:
      kind = CPTK_UNDERLYING_TYPE;
      break;
    case RID_BASES:
      kind = CPTK_BASES;
      break;
    case RID_DIRECT_BASES:
      kind = CPTK_DIRECT_BASES;
      break;
    default:
      gcc_unreachable ();
    }


  cp_lexer_consume_token (parser->lexer);

  cp_parser_require (parser, CPP_OPEN_PAREN, RT_OPEN_PAREN);

  type1 = cp_parser_type_id (parser);

  if (type1 == error_mark_node)
    return error_mark_node;


  clear_decl_specs (&decl_specs);
  decl_specs.type = type1;


  type1 = grokdeclarator (NULL, &decl_specs, TYPENAME,
			  0, NULL);

  if (binary)
    {
      cp_parser_require (parser, CPP_COMMA, RT_COMMA);

      type2 = cp_parser_type_id (parser);

      if (type2 == error_mark_node)
	return error_mark_node;


      clear_decl_specs (&decl_specs);
      decl_specs.type = type2;


      type2 = grokdeclarator (NULL, &decl_specs, TYPENAME,
			      0, NULL);
    }

  cp_parser_require (parser, CPP_CLOSE_PAREN, RT_CLOSE_PAREN);


  switch(kind)
    {
    case CPTK_UNDERLYING_TYPE:
      return finish_underlying_type (type1);
    case CPTK_BASES:
      return finish_bases (type1, false);
    case CPTK_DIRECT_BASES:
      return finish_bases (type1, true);
    default:
      return finish_trait_expr (kind, type1, type2);
    }
}
