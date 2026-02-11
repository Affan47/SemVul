cp_parser_mem_initializer_list (cp_parser* parser)
{
  tree mem_initializer_list = NULL_TREE;
  tree target_ctor = error_mark_node;
  cp_token *token = cp_lexer_peek_token (parser->lexer);


  if (!DECL_CONSTRUCTOR_P (current_function_decl))
    error_at (token->location,
	      "only constructors take member initializers");


  while (true)
    {
      tree mem_initializer;

      token = cp_lexer_peek_token (parser->lexer);

      mem_initializer = cp_parser_mem_initializer (parser);

      if (cp_lexer_next_token_is (parser->lexer, CPP_ELLIPSIS))
        {

          cp_lexer_consume_token (parser->lexer);


          if (mem_initializer != error_mark_node
              && !TYPE_P (TREE_PURPOSE (mem_initializer)))
            {
              error_at (token->location,
			"cannot expand initializer for member %<%D%>",
			TREE_PURPOSE (mem_initializer));
              mem_initializer = error_mark_node;
            }


          if (mem_initializer != error_mark_node)
            mem_initializer = make_pack_expansion (mem_initializer);
        }
      if (target_ctor != error_mark_node
	  && mem_initializer != error_mark_node)
	{
	  error ("mem-initializer for %qD follows constructor delegation",
		 TREE_PURPOSE (mem_initializer));
	  mem_initializer = error_mark_node;
	}

      if (mem_initializer != error_mark_node
	  && TYPE_P (TREE_PURPOSE (mem_initializer))
	  && same_type_p (TREE_PURPOSE (mem_initializer), current_class_type))
	{
	  maybe_warn_cpp0x (CPP0X_DELEGATING_CTORS);
	  if (mem_initializer_list)
	    {
	      error ("constructor delegation follows mem-initializer for %qD",
		     TREE_PURPOSE (mem_initializer_list));
	      mem_initializer = error_mark_node;
	    }
	  target_ctor = mem_initializer;
	}

      if (mem_initializer != error_mark_node)
	{
	  TREE_CHAIN (mem_initializer) = mem_initializer_list;
	  mem_initializer_list = mem_initializer;
	}

      if (cp_lexer_next_token_is_not (parser->lexer, CPP_COMMA))
	break;

      cp_lexer_consume_token (parser->lexer);
    }


  if (DECL_CONSTRUCTOR_P (current_function_decl))
    finish_mem_initializers (mem_initializer_list);
}
