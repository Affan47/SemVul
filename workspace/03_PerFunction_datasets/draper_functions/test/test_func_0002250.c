FSSetNextDrn(
	FDB *			pDb,
	BTSK *		pStack,
	FLMUINT		uiDrn,
	FLMBOOL		bManditoryChange)
{
	RCODE			rc = FERR_OK;
	FLMUINT		uiNextDrn;
	FLMBYTE *	ptr;
	FLMBYTE *	pBlk = GET_CABLKPTR( pStack );


	if( FB2UD( &pBlk[ BH_NEXT_BLK ]) == BT_END &&
		pStack->uiCurElm + 11 + BBE_LEM_LEN >= pStack->uiBlkEnd)
	{
		ptr = CURRENT_ELM( pStack);
		ptr += BBE_GETR_KL( ptr) + BBE_KEY;
		uiNextDrn = FB2UD( ptr);


		if( uiDrn >= uiNextDrn)
		{
			uiNextDrn = uiDrn + 1;

			if( RC_BAD( rc = FSLogPhysBlk( pDb, pStack)))
			{
				goto Exit;
			}

			ptr = CURRENT_ELM( pStack);
			ptr += BBE_GETR_KL( ptr) + BBE_KEY;


			UD2FBA( uiNextDrn, ptr);
			goto Exit;
		}
	}

	if( bManditoryChange)
	{
		rc = RC_SET( FERR_BTREE_ERROR);
		goto Exit;
	}

Exit:

	return( rc);
}
