pFreeOneList(list_mem_type *pAnchor)
{
	list_mem_type	*pCurr, *pNext;

	pCurr = pAnchor;
	while (pCurr != NULL) {
		pNext = pCurr->pNext;
		pCurr = xfree(pCurr);
		pCurr = pNext;
	}
	return NULL;
}
