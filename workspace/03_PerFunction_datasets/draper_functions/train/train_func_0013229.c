cp_lexer_get_preprocessor_token (cp_lexer *lexer ATTRIBUTE_UNUSED ,
                                 cp_token *token)
{
  bool done;


  if (lexer != NULL && !lexer->main_lexer_p)
    {
      token->type = CPP_EOF;
      token->location.line = 0;
      token->location.file = NULL;
      token->value = NULL_TREE;
      token->keyword = RID_MAX;

      return;
    }

  done = false;

  while (!done)
    {

      token->type = c_lex_with_flags (&token->value, &token->flags);

      switch (token->type)
	{
	case CPP_ATSIGN:
	case CPP_HASH:
	case CPP_PASTE:
	  error ("invalid token");
	  break;

	default:

	  done = true;
	  break;
	}
    }

  token->location = input_location;


  if (token->type == CPP_NAME
      && C_IS_RESERVED_WORD (token->value))
    {

      token->type = CPP_KEYWORD;

      token->keyword = C_RID_CODE (token->value);


      token->value = ridpointers[token->keyword];
    }
  else
    token->keyword = RID_MAX;
}
