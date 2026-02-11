FSCompareKeyPos(
	KEYSET *			pSet1,
	KEYSET *			pSet2,
	FLMBOOL *		pbFromKeyLessThan,
	FLMBOOL *		pbUntilKeyGreaterThan)
{

	if( FS_COMPARE_KEYS( TRUE, &pSet1->untilKey, FALSE, &pSet2->fromKey) < 0)
	{
		*pbFromKeyLessThan = TRUE;
		pbUntilKeyGreaterThan = FALSE;
		return FALSE;
	}

	if( FS_COMPARE_KEYS( FALSE, &pSet1->fromKey, TRUE, &pSet2->untilKey) > 0)
	{
		*pbFromKeyLessThan = FALSE;
		*pbUntilKeyGreaterThan = TRUE;
		return FALSE;
	}


	*pbFromKeyLessThan = (FLMBOOL) ((FS_COMPARE_KEYS( FALSE, &pSet1->fromKey,
				FALSE, &pSet2->fromKey) < 0) ? TRUE : FALSE);

	*pbUntilKeyGreaterThan = (FLMBOOL) ((FS_COMPARE_KEYS( TRUE, &pSet1->untilKey,
				TRUE, &pSet2->untilKey) > 0) ? TRUE : FALSE);

	return (TRUE);
}
