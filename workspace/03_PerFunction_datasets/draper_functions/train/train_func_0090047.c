AddStyledText(char *buffer, int appendLength) {

	int textLength = appendLength / 2;
	char *text = new char[textLength];
	int i;
	for (i = 0; i < textLength; i++) {
		text[i] = buffer[i*2];
	}
	pdoc->InsertString(CurrentPosition(), text, textLength);
	for (i = 0; i < textLength; i++) {
		text[i] = buffer[i*2+1];
	}
	pdoc->StartStyling(CurrentPosition(), static_cast<char>(0xff));
	pdoc->SetStyles(textLength, text);
	delete []text;
	SetEmptySelection(sel.MainCaret() + textLength);
}
