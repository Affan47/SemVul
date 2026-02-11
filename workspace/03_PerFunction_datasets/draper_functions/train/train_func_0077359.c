cp_parser_diagnose_invalid_type_name (cp_parser *parser)
{


  if (cp_lexer_next_token_is (parser->lexer, CPP_NAME)
      && cp_lexer_peek_nth_token (parser->lexer, 2)->type == CPP_NAME)
    {
      tree name;


      name = cp_lexer_consume_token (parser->lexer)->value;

      error ("`%s' does not name a type", IDENTIFIER_POINTER (name));


      if (processing_template_decl && current_class_type)
	{
	  tree b;

	  for (b = TREE_CHAIN (TYPE_BINFO (current_class_type));
	       b;
	       b = TREE_CHAIN (b))
	    {
	      tree base_type = BINFO_TYPE (b);
	      if (CLASS_TYPE_P (base_type)
		  && dependent_type_p (base_type))
		{
		  tree field;


		  base_type = CLASSTYPE_PRIMARY_TEMPLATE_TYPE (base_type);
		  for (field = TYPE_FIELDS (base_type);
		       field;
		       field = TREE_CHAIN (field))
		    if (TREE_CODE (field) == TYPE_DECL
			&& DECL_NAME (field) == name)
		      {
			error ("(perhaps `typename %T::%s' was intended)",
			       BINFO_TYPE (b), IDENTIFIER_POINTER (name));
			break;
		      }
		  if (field)
		    break;
		}
	    }
	}


      cp_parser_skip_to_end_of_statement (parser);

      return true;
    }

  return false;
}
