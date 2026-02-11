plpgsql_token_is_unreserved_keyword(int token)
{
	int			i;

	for (i = 0; i < num_unreserved_keywords; i++)
	{
		if (unreserved_keywords[i].value == token)
			return true;
	}
	return false;
}
