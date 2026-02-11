FSRefSearch(
	BTSK *			pStack,
	DIN_STATE *		pState,
	FLMUINT *		puiDin)
{
	FLMBYTE *		pCurRef;
	FLMBYTE *		pCurElm;
	FLMUINT			uiRefSize;
	FLMUINT			uiLastOffset;
	FLMUINT			uiDelta;
	FLMUINT			uiTargetDin = *puiDin;
	FLMUINT			uiDin;
	FLMUINT			uiOneRuns;
	DIN_STATE		tempState;
	FLMBYTE			byValue;


	pCurRef = pCurElm = CURRENT_ELM( pStack);
	(void) FSGetDomain( &pCurRef, pStack->uiElmOvhd);
	uiRefSize = (FLMUINT) (BBE_GET_RL( pCurElm) -
							(pCurRef - BBE_REC_PTR( pCurElm)));

	RESET_DINSTATE_p( pState);
	RESET_DINSTATE( tempState);

	uiLastOffset = tempState.uiOffset;
	uiDin = DINNextVal( pCurRef, &tempState);

	if (uiDin > uiTargetDin)
	{
		while (tempState.uiOffset < uiRefSize)
		{


			byValue = (FLMBYTE) pCurRef[uiLastOffset = tempState.uiOffset];

			if (DIN_IS_REAL_ONE_RUN( byValue))
			{
				uiOneRuns = DINOneRunVal( pCurRef, &tempState);


				if ((uiDin - uiOneRuns) <= uiTargetDin)
				{
					uiOneRuns = (uiDin - uiTargetDin) - 1;
					pState->uiOffset = uiLastOffset;
					pState->uiOnes = uiOneRuns;
					uiDin = uiTargetDin;
					break;
				}

				uiDin -= uiOneRuns;
			}
			else
			{
				uiDelta = DINNextVal( pCurRef, &tempState);


				uiDin -= uiDelta;
				if (uiDin <= uiTargetDin)
				{
					pState->uiOffset = uiLastOffset;
					break;
				}
			}
		}

		pState->uiOffset = uiLastOffset;
	}

	*puiDin = uiDin;
	return ((uiDin == uiTargetDin) ? FERR_OK : RC_SET( FERR_FAILURE));
}
