cp_parser_token_starts_function_definition_p (cp_token* token)
{
  return (
	  token->type == CPP_OPEN_BRACE

	  || token->type == CPP_COLON

	  || token->keyword == RID_TRY

	  || token->keyword == RID_RETURN);
}
