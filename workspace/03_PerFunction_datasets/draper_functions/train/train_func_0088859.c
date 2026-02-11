mCSTR(bool _createToken) {
	int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
	_ttype = CSTR;
	std::string::size_type _saveIndex;

	if ((((LA(1) >= 0x3   && LA(1) <= 0xff)) && (true))&&( doubleQuotes)) {
		{
		mCSTR1(false);
		{
		switch ( LA(1)) {
		case 0x22  :
		{
			_saveIndex = text.length();
			match('\"'  );
			text.erase(_saveIndex);
			selector->pop();
			break;
		}
		case 0x25  :
		{
			_saveIndex = text.length();
			match('%'  );
			text.erase(_saveIndex);
			format = true;
			break;
		}
		default:
		{
			throw antlr::NoViableAltForCharException(LA(1), getFilename(), getLine(), getColumn());
		}
		}
		}
		}
	}
	else if (((LA(1) >= 0x3   && LA(1) <= 0xff)) && (true)) {
		{
		mCSTR2(false);
		{
		switch ( LA(1)) {
		case 0x27  :
		{
			_saveIndex = text.length();
			match('\''  );
			text.erase(_saveIndex);
			selector->pop();
			break;
		}
		case 0x25  :
		{
			_saveIndex = text.length();
			match('%'  );
			text.erase(_saveIndex);
			format = true;
			break;
		}
		default:
		{
			throw antlr::NoViableAltForCharException(LA(1), getFilename(), getLine(), getColumn());
		}
		}
		}
		}
	}
	else {
		throw antlr::NoViableAltForCharException(LA(1), getFilename(), getLine(), getColumn());
	}

	if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
	   _token = makeToken(_ttype);
	   _token->setText(text.substr(_begin, text.length()-_begin));
	}
	_returnToken = _token;
	_saveIndex=0;
}
