FSGetBtreeRefPosition(
	FDB *				pDb,
	BTSK * 			pStack,
	DIN_STATE *		pDinState,
	FLMUINT *		puiRefPosition)
{
	RCODE				rc = FERR_OK;
	FLMUINT			uiTotalCount;
	FLMUINT			uiRefCount;

	F_UNREFERENCED_PARM( pDb);


	if( RC_BAD( rc = FSBlockCounts( pStack, BH_OVHD, pStack->uiCurElm,
			NULL, NULL, &uiTotalCount)))
	{
		goto Exit;
	}


	if( !pDinState->uiOffset)
	{
		uiTotalCount++;
	}
	else
	{
		FLMBYTE *		pCurRef;
		FLMBYTE *		pCurElm;
		FLMUINT			uiRefSize;
		DIN_STATE		tempState;


		uiRefCount = 2;
		RESET_DINSTATE( tempState );
		pCurRef = pCurElm = CURRENT_ELM( pStack );
		(void) FSGetDomain( &pCurRef, pStack->uiElmOvhd );
		uiRefSize = (FLMUINT)(BBE_GET_RL(pCurElm) -
									(pCurRef - BBE_REC_PTR(pCurElm)));


		(void) DINNextVal( pCurRef, &tempState );

		while( tempState.uiOffset < pDinState->uiOffset
			 && tempState.uiOffset < uiRefSize)
		{
			FLMUINT			uiNextLength;


			if( (uiNextLength = SENValLen( pCurRef + tempState.uiOffset)) == 0)
			{
				uiRefCount += DINOneRunVal( pCurRef, &tempState );
			}
			else
			{
				tempState.uiOffset += uiNextLength;
				uiRefCount++;
			}
		}

		if( tempState.uiOffset == pDinState->uiOffset && pDinState->uiOnes)
		{
			uiRefCount += pDinState->uiOnes;
		}

		uiTotalCount += uiRefCount;
	}


	while( !BH_IS_ROOT_BLK( pStack->pBlk))
	{


		pStack--;

		if( RC_BAD( rc = FSBlockCounts( pStack, BH_OVHD, pStack->uiCurElm,
				NULL, NULL, &uiRefCount)))
		{
			goto Exit;
		}

		uiTotalCount += uiRefCount;
	}

Exit:

	*puiRefPosition = uiTotalCount;
	return( rc);
}
