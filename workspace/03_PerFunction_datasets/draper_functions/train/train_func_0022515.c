GetWordListDescription(int index) const {
	static const char *emptyStr = "";

	assert(index < GetNumWordLists());
	if (index >= GetNumWordLists()) {
		return emptyStr;
	} else {
		return wordListDescriptions[index];
 	}
}
