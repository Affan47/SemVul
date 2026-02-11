Tok2Str(SQInteger tok)
{
	SQObjectPtr itr, key, val;
	SQInteger nitr;
	while((nitr = _keywords->Next(false,itr, key, val)) != -1) {
		itr = (SQInteger)nitr;
		if(((SQInteger)_integer(val)) == tok)
			return _stringval(key);
	}
	return NULL;
}
