HandleXml(char ch) {


	if (ch != '>') {
		return false;
	}


	if (lexLanguage != SCLEX_HTML && lexLanguage != SCLEX_XML) {
		return false;
	}


	SString value = props->GetExpanded("xml.auto.close.tags");
	if ((value.length() == 0) || (value == "0")) {
		return false;
	}


	int nCaret = SendEditor(SCI_GETCURRENTPOS);
	char sel[512];
	int nMin = nCaret - (sizeof(sel) - 1);
	if (nMin < 0) {
		nMin = 0;
	}

	if (nCaret - nMin < 3) {
		return false;
	}
	GetRange(wEditor, nMin, nCaret, sel);
	sel[sizeof(sel) - 1] = '\0';

	if (sel[nCaret - nMin - 2] == '/') {

		return false;
	}

	SString strFound = FindOpenXmlTag(sel, nCaret - nMin);

	if (strFound.length() > 0) {
		SendEditor(SCI_BEGINUNDOACTION);
		SString toInsert = "</";
		toInsert += strFound;
		toInsert += ">";
		SendEditorString(SCI_REPLACESEL, 0, toInsert.c_str());
		SetSelection(nCaret, nCaret);
		SendEditor(SCI_ENDUNDOACTION);
		return true;
	}

	return false;
}
