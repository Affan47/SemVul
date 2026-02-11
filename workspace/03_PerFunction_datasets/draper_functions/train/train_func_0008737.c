find(const Node* pParent, unsigned long index) const
{
	if (!pParent) return 0;


	Node* pCur = pParent->firstChild();
	while (pCur)
	{
		if (pCur->nodeType() == Node::ELEMENT_NODE && (_name == asterisk || pCur->nodeName() == _name))
		{
			if (_count == index) return pCur;
			_count++;
		}
		Node* pNode = find(pCur, index);
		if (pNode) return pNode;
		pCur = pCur->nextSibling();
	}
	return pCur;
}
