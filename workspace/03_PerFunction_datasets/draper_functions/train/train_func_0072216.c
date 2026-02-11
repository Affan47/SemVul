GotoMetadataItem(int nItemNumber)
{
	if (nItemNumber > nMetadataCount || nItemNumber < 0) {
		nItemNumber = 0;
		return 0;
	}
	nCurrentItem = nItemNumber;
	return nCurrentItem;
}
