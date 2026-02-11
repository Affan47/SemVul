FindOpenXmlTag(const char sel[], int nSize) {
	SString strRet = "";

	if (nSize < 3) {

		return strRet;
	}
	const char* pBegin = &sel[0];
	const char* pCur = &sel[nSize - 1];

	pCur--;
	while (pCur > pBegin) {
		if (*pCur == '<') {
			break;
		} else if (*pCur == '>') {
			break;
		}
		--pCur;
	}

	if (*pCur == '<') {
		pCur++;
		while (strchr(":_-.", *pCur) || isalnum(*pCur)) {
			strRet += *pCur;
			pCur++;
		}
	}


	return strRet;
}
