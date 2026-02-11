bExamineDIB(FILE *pFile, imagedata_type *pImg)
{
	size_t	tHeaderSize;
	int	iPlanes, iCompression;

	tHeaderSize = (size_t)ulNextLong(pFile);
	switch (tHeaderSize) {
	case 12:
		pImg->iWidth = (int)usNextWord(pFile);
		pImg->iHeight = (int)usNextWord(pFile);
		iPlanes = (int)usNextWord(pFile);
		pImg->uiBitsPerComponent = (UINT)usNextWord(pFile);
		iCompression = BI_RGB;
		pImg->iColorsUsed = 0;
		break;
	case 40:
	case 64:
		pImg->iWidth = (int)ulNextLong(pFile);
		pImg->iHeight = (int)ulNextLong(pFile);
		iPlanes = (int)usNextWord(pFile);
		pImg->uiBitsPerComponent = (UINT)usNextWord(pFile);
		iCompression = (int)ulNextLong(pFile);
		(void)tSkipBytes(pFile, 12);
		pImg->iColorsUsed = (int)ulNextLong(pFile);
		(void)tSkipBytes(pFile, tHeaderSize - 36);
		break;
	default:
		DBG_DEC(tHeaderSize);
		return FALSE;
	}
	DBG_DEC(pImg->iWidth);
	DBG_DEC(pImg->iHeight);
	DBG_DEC(pImg->uiBitsPerComponent);
	DBG_DEC(iCompression);
	DBG_DEC(pImg->iColorsUsed);


	if (iPlanes != 1) {
		DBG_DEC(iPlanes);
		return FALSE;
	}
	if (pImg->iWidth <= 0 || pImg->iHeight <= 0) {
		DBG_DEC(pImg->iWidth);
		DBG_DEC(pImg->iHeight);
		return FALSE;
	}
	if (pImg->uiBitsPerComponent != 1 && pImg->uiBitsPerComponent != 4 &&
	    pImg->uiBitsPerComponent != 8 && pImg->uiBitsPerComponent != 24) {
		DBG_DEC(pImg->uiBitsPerComponent);
		return FALSE;
	}
	if (iCompression != BI_RGB &&
	    (pImg->uiBitsPerComponent == 1 || pImg->uiBitsPerComponent == 24)) {
		return FALSE;
	}
	if (iCompression == BI_RLE8 && pImg->uiBitsPerComponent == 4) {
		return FALSE;
	}
	if (iCompression == BI_RLE4 && pImg->uiBitsPerComponent == 8) {
		return FALSE;
	}

	switch (iCompression) {
	case BI_RGB:
		pImg->eCompression = compression_none;
		break;
	case BI_RLE4:
		pImg->eCompression = compression_rle4;
		break;
	case BI_RLE8:
		pImg->eCompression = compression_rle8;
		break;
	default:
		DBG_DEC(iCompression);
		return FALSE;
	}

	pImg->bColorImage = bFillPaletteDIB(pFile, pImg, tHeaderSize > 12);

	if (pImg->uiBitsPerComponent <= 8) {
		pImg->iComponents = 1;
	} else {
		pImg->iComponents = (int)(pImg->uiBitsPerComponent / 8);
	}

	return TRUE;
}
