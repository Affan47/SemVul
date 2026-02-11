item(unsigned long index) const
{
	unsigned long n = 0;
	Node* pCur = _pParent->firstChild();
	while (pCur && n++ < index)
	{
		pCur = pCur->nextSibling();
	}
	return pCur;
}
