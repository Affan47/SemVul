flmCurCopyQTInfo(
	QTINFO *		pSrc,
	QTINFO *		pDest,
	F_Pool *		pPool)
{
	RCODE			rc = FERR_OK;
	FQNODE *		pDestParentNode;
	FQNODE *		pSrcCurrNode;
	FQNODE *		pDestCurrNode;
	FLMBOOL		bGoingUp = FALSE;
	FLMBOOL		bTreeComplete;


	if (pSrc->pSaveQuery)
	{
		pSrcCurrNode = pSrc->pSaveQuery;
		bTreeComplete = TRUE;
	}
	else
	{
		pSrcCurrNode = pSrc->pTopNode;
		bTreeComplete = FALSE;
		pDest->pCurOpNode = NULL;
		pDest->pCurAtomNode = NULL;
	}


	if (pSrcCurrNode)
	{


		if (RC_BAD( rc = flmCurCopyQNode( pSrcCurrNode, pDest,
										&pDest->pTopNode, pPool)))
		{
			goto Exit;
		}
		pDestParentNode = NULL;
		pDestCurrNode = pDest->pTopNode;
		if (!bTreeComplete)
		{
			if (pSrcCurrNode == pSrc->pCurOpNode)
			{
				pDest->pCurOpNode = pDestCurrNode;
			}
			else if (pSrcCurrNode == pSrc->pCurAtomNode)
			{
				pDest->pCurAtomNode = pDestCurrNode;
			}
		}
		for (;;)
		{
			if (bGoingUp)
			{
				if (pSrcCurrNode->pNextSib)
				{
					pSrcCurrNode = pSrcCurrNode->pNextSib;
					bGoingUp = FALSE;
				}
				else if ((pSrcCurrNode = pSrcCurrNode->pParent) == NULL)
				{
					break;
				}
				else
				{
					pDestCurrNode = pDestCurrNode->pParent;
					pDestParentNode = pDestCurrNode->pParent;
					continue;
				}
			}
			else
			{
				if (pSrcCurrNode->pChild)
				{
					pSrcCurrNode = pSrcCurrNode->pChild;
					pDestParentNode = pDestCurrNode;
				}
				else
				{
					bGoingUp = TRUE;
					continue;
				}
			}
			if (RC_BAD( rc = flmCurCopyQNode( pSrcCurrNode, pDest,
										&pDestCurrNode, pPool)))
			{
				goto Exit;
			}

			flmCurLinkLastChild( pDestParentNode, pDestCurrNode);
			if (!bTreeComplete)
			{
				if (pSrcCurrNode == pSrc->pCurOpNode)
				{
					pDest->pCurOpNode = pDestCurrNode;
				}
				else if( pSrcCurrNode == pSrc->pCurAtomNode)
				{
					pDest->pCurAtomNode = pDestCurrNode;
				}
			}
		}
	}

	if (bTreeComplete)
	{
		pDest->pCurOpNode = pDest->pTopNode;
		pDest->uiNestLvl = 0;
		pDest->pCurAtomNode = NULL;
		if (pDest->pTopNode)
		{
			pDest->uiExpecting = FLM_Q_OPERATOR;
		}
		else
		{
			pDest->uiExpecting = FLM_Q_OPERAND;
		}
	}
	else
	{
		pDest->uiNestLvl = pSrc->uiNestLvl;
		pDest->uiExpecting = pSrc->uiExpecting;


		if (!pDest->pTopNode)
		{
			if (pSrc->pCurOpNode)
			{
				if (RC_BAD( rc = flmCurCopyQNode( pSrc->pCurOpNode,
											pDest, &pDest->pCurOpNode, pPool)))
				{
					goto Exit;
				}
			}
			if (pSrc->pCurAtomNode)
			{
				if (RC_BAD( rc = flmCurCopyQNode( pSrc->pCurAtomNode,
					pDest, &pDest->pCurAtomNode, pPool)))
				{
					goto Exit;
				}
			}
		}
	}

	pDest->uiFlags = pSrc->uiFlags;

Exit:
	return( rc);
}
