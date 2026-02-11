disambiguateBareword(LexAccessor &styler, unsigned int bk, unsigned int fw,
        int backFlag, unsigned int backPos, unsigned int endPos) {


	int result = 0;
	bool moreback = false;
	bool brace = false;

	if (backFlag == BACK_NONE)
		return result;


	if (backPos <= static_cast<unsigned int>(styler.LineStart(styler.GetLine(bk))))
		moreback = true;

	bk = backPos - 1;
	int ch = static_cast<unsigned char>(styler.SafeGetCharAt(bk));
	if (ch == '{' && !moreback) {

		brace = true;
	} else if ((ch == '&' && styler.SafeGetCharAt(bk - 1) != '&')

	        || styler.Match(bk - 1, "->")

	        || styler.Match(bk - 2, "sub")) {


		result |= 1;
	}


	if ((ch == '{' || ch == '(' || ch == '['|| ch == ',')
	        && fw < endPos) {
		while (ch = static_cast<unsigned char>(styler.SafeGetCharAt(fw)),
		        IsASpaceOrTab(ch) && fw < endPos) {
			fw++;
		}
		if ((ch == '}' && brace)

		        || styler.Match(fw, "=>")) {

			result |= 2;
		}
	}
	return result;
}
