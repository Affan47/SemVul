mNUMBER(bool _createToken) {
	int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
	_ttype = NUMBER;
	std::string::size_type _saveIndex;
	antlr::RefToken num;

	SizeT n;
	SizeT i = 0;
	bool uMinus = false;


	{
	switch ( LA(1)) {
	case 0x2d  :
	{
		match('-'  );

		uMinus = true;

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
	mDIGITS(true);
	num=_returnToken;

	if( uMinus) num->setText( "-" + num->getText());

	{
	if ((LA(1) == 0x48  )) {

		_ttype = STRING;
		std::istringstream s(num->getText());
		s >> n;
		{ text.erase(_begin); text += ""; };

		_saveIndex = text.length();
		match('H'  );
		text.erase(_saveIndex);
		{
		int _cnt130=0;
		for (;;) {

			if( i == n )
			break;
			i++;

			if (((LA(1) >= 0x3   && LA(1) <= 0xff))) {
				mCHAR(false);
			}
			else {
				if ( _cnt130>=1 ) { goto _loop130; } else {throw antlr::NoViableAltForCharException(LA(1), getFilename(), getLine(), getColumn());}
			}

			_cnt130++;
		}
		_loop130:;
		}
	}
	else {
	}

	}
	if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
	   _token = makeToken(_ttype);
	   _token->setText(text.substr(_begin, text.length()-_begin));
	}
	_returnToken = _token;
	_saveIndex=0;
}
