AutoCompleteMoveToCurrentWord() {
	std::string wordCurrent = RangeText(ac.posStart - ac.startLen, sel.MainCaret());
	ac.Select(wordCurrent.c_str());
}
