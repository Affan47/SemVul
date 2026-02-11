SearchInTarget(const char *text, int length) {
	int lengthFound = length;

	if (!pdoc->HasCaseFolder())
		pdoc->SetCaseFolder(CaseFolderForEncoding());
	int pos = pdoc->FindText(targetStart, targetEnd, text,
	        (searchFlags & SCFIND_MATCHCASE) != 0,
	        (searchFlags & SCFIND_WHOLEWORD) != 0,
	        (searchFlags & SCFIND_WORDSTART) != 0,
	        (searchFlags & SCFIND_REGEXP) != 0,
	        searchFlags,
	        &lengthFound);
	if (pos != -1) {
		targetStart = pos;
		targetEnd = pos + lengthFound;
	}
	return pos;
}
