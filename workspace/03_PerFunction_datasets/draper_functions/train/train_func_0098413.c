scaSetFlags(
	SCACHE *		pSCache,
	FLMUINT16	ui16FlagsToSet
	)
{
	flmAssert( ui16FlagsToSet);

	if( !pSCache->ui16Flags)
	{
		ScaUnlinkFromReplaceList( pSCache);
	}
	pSCache->ui16Flags |= ui16FlagsToSet;
}
