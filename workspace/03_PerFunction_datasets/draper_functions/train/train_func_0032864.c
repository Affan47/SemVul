bGetCodesetFromLocale(char *szCodeset, size_t tMaxCodesetLength, BOOL *pbEuro)
{
#if !defined(__dos)
	const char	*szLocale;
	const char	*pcTmp;
	size_t		tIndex;
	char		szModifier[6];
#endif

	if (pbEuro != NULL) {
		*pbEuro = FALSE;
	}
	if (szCodeset == NULL || tMaxCodesetLength == 0) {
		return FALSE;
	}

#if defined(__dos)
	if (tMaxCodesetLength < 2 + sizeof(int) * 3 + 1) {
		DBG_DEC(tMaxCodesetLength);
		DBG_DEC(2 + sizeof(int) * 3 + 1);
		return FALSE;
	}

	sprintf(szCodeset, "cp%d", iGetCodepage());
	DBG_MSG(szCodeset);
#else

	szLocale = getenv("LC_ALL");
	if (szLocale == NULL || szLocale[0] == '\0') {
		szLocale = getenv("LC_CTYPE");
		if (szLocale == NULL || szLocale[0] == '\0') {
			szLocale = getenv("LANG");
		}
	}
	if (szLocale == NULL || szLocale[0] == '\0') {

		return FALSE;
	}
	DBG_MSG(szLocale);
	pcTmp = strchr(szLocale, '.');
	if (pcTmp == NULL) {

		szCodeset[0] = '\0';
	} else {

		pcTmp++;
		for (tIndex = 0; tIndex < tMaxCodesetLength; tIndex++) {
			if (*pcTmp == '@' || *pcTmp == '+' ||
			    *pcTmp == ',' || *pcTmp == '_' ||
			    *pcTmp == '\0') {
				szCodeset[tIndex] = '\0';
				break;
			}
			szCodeset[tIndex] = *pcTmp;
			pcTmp++;
		}
		szCodeset[tMaxCodesetLength - 1] = '\0';
	}
	if (pbEuro == NULL) {

		return TRUE;
	}
	pcTmp = strchr(szLocale, '@');
	if (pcTmp != NULL) {

		pcTmp++;
		for (tIndex = 0; tIndex < sizeof(szModifier); tIndex++) {
			if (*pcTmp == '+' || *pcTmp == ',' ||
			    *pcTmp == '_' || *pcTmp == '\0') {
				szModifier[tIndex] = '\0';
				break;
			}
			szModifier[tIndex] = *pcTmp;
			pcTmp++;
		}
		szModifier[sizeof(szModifier) - 1] = '\0';
		*pbEuro = STRCEQ(szModifier, "Euro");
	}
#endif
	return TRUE;
}
