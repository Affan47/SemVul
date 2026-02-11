factor(int output)
{
    if(match('"'))
    {
	phrase(output);
    }
    else if (match('('))
    {
	expr(output);
	if (match(')'))
	{
	    return;
	}
	else
	{
	    setError("')'");
	}
    }
    else if (lookahead == WORD)
    {
	if (output)
	{
	    perform_push();
	}
	lookahead = lexan();
    }
    else
    {
    	setError(boolean_syntax_errors[SEARCH_WORD]);

    }
}
