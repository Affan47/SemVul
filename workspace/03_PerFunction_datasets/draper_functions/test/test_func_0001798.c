vGet0SectionInfo(const UCHAR *aucGrpprl, size_t tBytes,
		section_block_type *pSection)
{
	USHORT	usCcol;
	UCHAR	ucTmp;

	fail(aucGrpprl == NULL || pSection == NULL);

	if (tBytes < 2) {
		return;
	}

	ucTmp = ucGetByte(1, aucGrpprl);
	DBG_HEX(ucTmp);
	ucTmp &= 0x07;
	DBG_HEX(ucTmp);
	pSection->bNewPage = ucTmp != 0 && ucTmp != 1;
	if (tBytes < 18) {
		return;
	}

	usCcol = (USHORT)ucGetByte(17, aucGrpprl);
	DBG_DEC(usCcol);
}
