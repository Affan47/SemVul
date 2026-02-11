flmCurLinkFirstChild(
	FQNODE * pParent,
	FQNODE * pChild
	)
{
	FQNODE *	pTmpQNode;


	if (pChild->pPrevSib)
	{
		pChild->pPrevSib->pNextSib = pChild->pNextSib;
		if (pChild->pNextSib)
		{
			pChild->pNextSib->pPrevSib = pChild->pPrevSib;
		}
		for (pTmpQNode = pChild;
				pTmpQNode->pPrevSib;
				pTmpQNode = pTmpQNode->pPrevSib)
		{
			;
		}
		pChild->pNextSib = pTmpQNode;
		pTmpQNode->pPrevSib = pChild;
	}


	if (pParent->pChild)
	{
		for (pTmpQNode = pChild;
				pTmpQNode->pNextSib;
				pTmpQNode = pTmpQNode->pNextSib)
		{
			pTmpQNode->pParent = pParent;
		}
		pParent->pChild->pPrevSib = pTmpQNode;
		pTmpQNode->pNextSib = pParent->pChild;
	}
	pParent->pChild = pChild;
	pChild->pParent = pParent;
	pChild->pPrevSib = NULL;
}
