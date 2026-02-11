endCDATA()
{
	if (_pLexicalHandler)
		_pLexicalHandler->endCDATA();
	_filter = true;
	_data.clear();
}
