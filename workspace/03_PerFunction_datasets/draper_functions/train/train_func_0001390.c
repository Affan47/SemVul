CopyText(int length, const char *text) {
	SelectionText selectedText;
	selectedText.Copy(std::string(text, length),
		pdoc->dbcsCodePage, vs.styles[STYLE_DEFAULT].characterSet, false, false);
	CopyToClipboard(selectedText);
}
