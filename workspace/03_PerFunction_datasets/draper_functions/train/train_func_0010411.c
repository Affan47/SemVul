ColouriseDocument(
    unsigned int startPos,
    int length,
    int initStyle,
    WordList *keywordlists[],
    Accessor &styler) {
	WordList &keywords = *keywordlists[0];

	StyleContext sc(startPos, length, initStyle, styler);

	int lineCurrent = styler.GetLine(startPos);
	bool apostropheStartsAttribute = (styler.GetLineState(lineCurrent) & 1) != 0;

	while (sc.More()) {
		if (sc.atLineEnd) {

			sc.Forward();
			lineCurrent++;


			styler.SetLineState(lineCurrent, apostropheStartsAttribute);


			sc.SetState(SCE_ADA_DEFAULT);
		}


		if (sc.Match('-', '-')) {
			ColouriseComment(sc, apostropheStartsAttribute);


		} else if (sc.Match('"')) {
			ColouriseString(sc, apostropheStartsAttribute);


		} else if (sc.Match('\'') && !apostropheStartsAttribute) {
			ColouriseCharacter(sc, apostropheStartsAttribute);


		} else if (sc.Match('<', '<')) {
			ColouriseLabel(sc, keywords, apostropheStartsAttribute);


		} else if (IsASpace(sc.ch)) {
			ColouriseWhiteSpace(sc, apostropheStartsAttribute);


		} else if (IsDelimiterCharacter(sc.ch)) {
			ColouriseDelimiter(sc, apostropheStartsAttribute);


		} else if (IsADigit(sc.ch) || sc.ch == '#') {
			ColouriseNumber(sc, apostropheStartsAttribute);


		} else {
			ColouriseWord(sc, keywords, apostropheStartsAttribute);
		}
	}

	sc.Complete();
}
