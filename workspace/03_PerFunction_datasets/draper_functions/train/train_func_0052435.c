pGetListInfo(USHORT usListIndex, UCHAR ucListLevel)
{
	list_desc_type	*pCurr;
	list_block_type	*pNearMatch;
	ULONG	ulListID;

	if (usListIndex == 0) {
		return NULL;
	}
	if (usListIndex - 1 >= usLfoLen || ucListLevel > 8) {
		DBG_DEC(usListIndex);
		DBG_DEC(ucListLevel);
		return NULL;
	}
	fail(aulLfoList == NULL);
	ulListID = aulLfoList[usListIndex - 1];
	NO_DBG_HEX(ulListID);

	pNearMatch = NULL;
	for (pCurr = pAnchor; pCurr != NULL; pCurr = pCurr->pNext) {
		if (pCurr->ulListID != ulListID) {

			continue;
		}
		if (pCurr->ucListLevel == ucListLevel) {

			return &pCurr->tInfo;
		}
		if (pCurr->ucListLevel == 0) {

			pNearMatch = &pCurr->tInfo;
		}
	}

	return pNearMatch;
}
