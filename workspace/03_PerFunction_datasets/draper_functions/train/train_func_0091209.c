nextNode()
{
	if (!_pCurrent) return 0;

	Node* pNext = next(_pCurrent);
	while (pNext && accept(pNext) != NodeFilter::FILTER_ACCEPT)
		pNext = next(pNext);
	if (pNext)
		_pCurrent = pNext;
	return pNext;
}
