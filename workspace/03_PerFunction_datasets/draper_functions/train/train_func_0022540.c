DRNCompareFunc(
	void *	pvData1,
	void *	pvData2,
	void *
	)
{
	if( *((FLMUINT *)pvData1) < *((FLMUINT *)pvData2))
	{
		return -1;
	}
	else if( *((FLMUINT *)pvData1) > *((FLMUINT *)pvData2))
	{
		return 1;
	}
	return 0;
}
