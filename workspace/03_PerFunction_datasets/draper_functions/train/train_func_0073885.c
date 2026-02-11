ParseExpression()
{
	Query *result = 0;
	Query *term = ParseTerm();
	if(term)
	{
		if(token.IsEnd())
		{
			result = term;
		}
		else
		{
			result = MakeQuery();
			result->Add(term);
			while(!token.IsEnd())
			{
				term = ParseTerm();
				if(term)
				{
					result->Add(term);
				}
			}
		}
	}
	if(!term)
	{
		delete result;
		result = 0;
	}
	return result;
}
