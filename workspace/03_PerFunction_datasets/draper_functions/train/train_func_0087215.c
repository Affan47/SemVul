bGetNormalizedCodeset(char *szCodeset, size_t tMaxCodesetLength, BOOL *pbEuro)
{
	BOOL	bOnlyDigits;
	const char	*pcSrc;
	char	*pcDest;
	char	*szTmp, *szCodesetNorm;

	if (pbEuro != NULL) {
		*pbEuro = FALSE;
	}
	if (szCodeset == NULL || tMaxCodesetLength < 4) {
		return FALSE;
	}


	szTmp = xmalloc(tMaxCodesetLength - 3);
	if (!bGetCodesetFromLocale(szTmp, tMaxCodesetLength - 3, pbEuro)) {
		szTmp = xfree(szTmp);
		return FALSE;
	}

	szCodesetNorm = xmalloc(tMaxCodesetLength - 3);
	bOnlyDigits = TRUE;
	pcDest = szCodesetNorm;
	for (pcSrc = szTmp; *pcSrc != '\0'; pcSrc++) {
		if (isalnum(*pcSrc)) {
			*pcDest = tolower(*pcSrc);
			if (!isdigit(*pcDest)) {
				bOnlyDigits = FALSE;
			}
			pcDest++;
		}
	}
	*pcDest = '\0';
	DBG_MSG(szCodesetNorm);

	if (bOnlyDigits && szCodesetNorm[0] != '\0') {
		fail(strlen(szCodesetNorm) + 3 >= tMaxCodesetLength);
		sprintf(szCodeset, "iso%s", szCodesetNorm);
	} else {
		fail(strlen(szCodesetNorm) >= tMaxCodesetLength);
		strncpy(szCodeset, szCodesetNorm, pcDest - szCodesetNorm + 1);
		szCodeset[tMaxCodesetLength - 1] = '\0';
	}
	DBG_MSG(szCodeset);

	szCodesetNorm = xfree(szCodesetNorm);
	szTmp = xfree(szTmp);
	return TRUE;
}
