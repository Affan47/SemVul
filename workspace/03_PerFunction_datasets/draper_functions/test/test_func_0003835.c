ParsePhrase()
{
	Query *result = 0;
	Query *word = 0;
	if(!Token().IsEnd() && !Token().IsQuote())
	{
		word = ParseExactWord();
	}
	if(word)
	{
		result = new PhraseQuery;
		result->Add(word);
		while(word && !Token().IsEnd() && !Token().IsQuote())
		{
			word = ParseExactWord();
			if(word)
			{
				result->Add(word);
			}
		}
	}
	if(!word && result)
	{
		delete result;
		result = 0;
	}
	if(!result)
	{
		Expected("at least one word after \"");
	}
	return result;
}
