GetNextItem()
{
	COASPMetadataItem *poMetadata;
	char **papszMDTokens;
	char *pszItemName;
	char *pszItemValue;
	if (nCurrentItem >= nMetadataCount)
		return NULL;


	papszMDTokens = CSLTokenizeString2(papszMetadata[nCurrentItem], " ",
		CSLT_HONOURSTRINGS );
	pszItemName = papszMDTokens[0];
	if (EQUALN(pszItemName, "georef_grid", 11)) {
		double ndLat, ndLong;
		int nPixels, nLines;


		nPixels = atoi(papszMDTokens[2]);
		nLines = atoi(papszMDTokens[3]);
		ndLat = CPLAtof(papszMDTokens[6]);
		ndLong = CPLAtof(papszMDTokens[7]);
		poMetadata = new COASPMetadataGeorefGridItem(nCurrentItem, nPixels,
			nLines, ndLat, ndLong);
	}
	else {
		int nCount = CSLCount(papszMDTokens);
		pszItemValue = strdup(papszMDTokens[1]);
		for (int i = 2; i < nCount; i++) {
			int nSize = strlen(papszMDTokens[i]);
			pszItemValue = (char *)CPLRealloc(pszItemValue,
				strlen(pszItemValue) + 1 + nSize);
			sprintf(pszItemValue,"%s %s",pszItemValue,
				papszMDTokens[i]);
		}

		poMetadata = new COASPMetadataItem(pszItemName,
			pszItemValue);

		free(pszItemValue);
	}
	free(pszItemName);
	nCurrentItem++;
	return poMetadata;
}
