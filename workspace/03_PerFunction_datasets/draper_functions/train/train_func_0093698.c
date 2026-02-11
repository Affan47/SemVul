ColouriseNullDoc(unsigned int startPos, int length, int, WordList *[],
                            Accessor &styler) {

	if (length > 0) {
		styler.StartAt(startPos + length - 1);
		styler.StartSegment(startPos + length - 1);
		styler.ColourTo(startPos + length - 1, 0);
	}
}
