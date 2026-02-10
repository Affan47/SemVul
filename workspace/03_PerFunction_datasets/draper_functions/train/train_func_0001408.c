find_in_aPlusBlk( Junction *alt )
#else
find_in_aPlusBlk( alt )
Junction *alt;
#endif
{
	require(alt!=NULL&&alt->p2!=NULL, "invalid aPlusBlk");
	return find_in_aSubBlk( alt );
}
