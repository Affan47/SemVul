cp_lexer_set_source_position_from_token (cp_lexer *lexer ATTRIBUTE_UNUSED ,
                                         const cp_token *token)
{


  if (token->type != CPP_EOF)
    input_location = token->location;
}
