SearchText(
    unsigned int iMessage,
    uptr_t wParam,

    sptr_t lParam) {

	const char *txt = reinterpret_cast<char *>(lParam);
	int pos;
	int lengthFound = istrlen(txt);
	ScopedCaseFolder pcf(CaseFolderForEncoding());
	if (iMessage == SCI_SEARCHNEXT) {
		pos = pdoc->FindText(searchAnchor, pdoc->Length(), txt,
		        (wParam & SCFIND_MATCHCASE) != 0,
		        (wParam & SCFIND_WHOLEWORD) != 0,
		        (wParam & SCFIND_WORDSTART) != 0,
		        (wParam & SCFIND_REGEXP) != 0,
		        wParam,
		        &lengthFound,
				pcf.get());
	} else {
		pos = pdoc->FindText(searchAnchor, 0, txt,
		        (wParam & SCFIND_MATCHCASE) != 0,
		        (wParam & SCFIND_WHOLEWORD) != 0,
		        (wParam & SCFIND_WORDSTART) != 0,
		        (wParam & SCFIND_REGEXP) != 0,
		        wParam,
		        &lengthFound,
				pcf.get());
	}
	if (pos != -1) {
		SetSelection(pos, pos + lengthFound);
	}

	return pos;
}
