mSL_COMMENT(bool _createToken) {
	int _ttype; ANTLR_USE_NAMESPACE(antlr)RefToken _token; ANTLR_USE_NAMESPACE(std)string::size_type _begin = text.length();
	_ttype = SL_COMMENT;
	ANTLR_USE_NAMESPACE(std)string::size_type _saveIndex;

	match("//");
	{
	for (;;) {
		if ((_tokenSet_3.member(LA(1)))) {
			{
			match(_tokenSet_3);
			}
		}
		else {
			goto _loop65;
		}

	}
	_loop65:;
	}
	{
	if ((LA(1) == 0xa  )) {
		match('\n'  );
	}
	else {
	}

	}
	if ( inputState->guessing==0 ) {

		newline();
		_ttype = antlr::Token::SKIP;

	}
	if ( _createToken && _token==ANTLR_USE_NAMESPACE(antlr)nullToken && _ttype!=ANTLR_USE_NAMESPACE(antlr)Token::SKIP ) {
	   _token = makeToken(_ttype);
	   _token->setText(text.substr(_begin, text.length()-_begin));
	}
	_returnToken = _token;
	_saveIndex=0;
}
