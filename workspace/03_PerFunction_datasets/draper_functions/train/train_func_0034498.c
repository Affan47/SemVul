mDBL(bool _createToken) {
	int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
	_ttype = DBL;
	std::string::size_type _saveIndex;

	{
	mDBL_E(false);
	{
	if ((_tokenSet_3.member(LA(1)))) {
		{
		switch ( LA(1)) {
		case 0x2b  :
		{
			match('+'  );
			break;
		}
		case 0x2d  :
		{
			match('-'  );
			break;
		}
		case 0x30  :
		case 0x31  :
		case 0x32  :
		case 0x33  :
		case 0x34  :
		case 0x35  :
		case 0x36  :
		case 0x37  :
		case 0x38  :
		case 0x39  :
		{
			break;
		}
		default:
		{
			throw antlr::NoViableAltForCharException(LA(1), getFilename(), getLine(), getColumn());
		}
		}
		}
		{
		int _cnt342=0;
		for (;;) {
			if (((LA(1) >= 0x30   && LA(1) <= 0x39  ))) {
				mD(false);
			}
			else {
				if ( _cnt342>=1 ) { goto _loop342; } else {throw antlr::NoViableAltForCharException(LA(1), getFilename(), getLine(), getColumn());}
			}

			_cnt342++;
		}
		_loop342:;
		}
	}
	else {
	}

	}
	}
	if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
	   _token = makeToken(_ttype);
	   _token->setText(text.substr(_begin, text.length()-_begin));
	}
	_returnToken = _token;
	_saveIndex=0;
}
