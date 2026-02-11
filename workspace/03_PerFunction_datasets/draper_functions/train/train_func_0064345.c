vDecode1bpp(FILE *pInFile, FILE *pOutFile, const imagedata_type *pImg)
{
	size_t	tPadding;
	int	iX, iY, iN, iByte, iTmp, iEighthWidth, iUse;

	DBG_MSG("vDecode1bpp");

	fail(pOutFile == NULL);
	fail(pImg == NULL);
	fail(pImg->iColorsUsed < 1 || pImg->iColorsUsed > 2);

	DBG_DEC(pImg->iWidth);
	DBG_DEC(pImg->iHeight);

	iEighthWidth = (pImg->iWidth + 7) / 8;
	tPadding = (size_t)(ROUND4(iEighthWidth) - iEighthWidth);

	for (iY = 0; iY < pImg->iHeight; iY++) {
		for (iX = 0; iX < iEighthWidth; iX++) {
			iByte = iNextByte(pInFile);
			if (iByte == EOF) {
				vASCII85EncodeByte(pOutFile, EOF);
				return;
			}
			if (iX == iEighthWidth - 1 && pImg->iWidth % 8 != 0) {
				iUse = pImg->iWidth % 8;
			} else {
				iUse = 8;
			}
			for (iN = 0; iN < iUse; iN++) {
				switch (iN) {
				case 0: iTmp = (iByte & 0x80) / 128; break;
				case 1: iTmp = (iByte & 0x40) / 64; break;
				case 2: iTmp = (iByte & 0x20) / 32; break;
				case 3: iTmp = (iByte & 0x10) / 16; break;
				case 4: iTmp = (iByte & 0x08) / 8; break;
				case 5: iTmp = (iByte & 0x04) / 4; break;
				case 6: iTmp = (iByte & 0x02) / 2; break;
				case 7: iTmp = (iByte & 0x01); break;
				default: iTmp = 0; break;
				}
				vASCII85EncodeByte(pOutFile, iTmp);
			}
		}
		(void)tSkipBytes(pInFile, tPadding);
	}
	vASCII85EncodeByte(pOutFile, EOF);
}
