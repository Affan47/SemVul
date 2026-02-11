removeChild(Node* oldChild)
{
	poco_check_ptr (oldChild);

	bool doEvents = events();
	if (oldChild == _pFirstChild)
	{
		if (doEvents)
		{
			static_cast<AbstractNode*>(oldChild)->dispatchNodeRemoved();
			static_cast<AbstractNode*>(oldChild)->dispatchNodeRemovedFromDocument();
		}
		_pFirstChild = _pFirstChild->_pNext;
		static_cast<AbstractNode*>(oldChild)->_pNext   = 0;
		static_cast<AbstractNode*>(oldChild)->_pParent = 0;
	}
	else
	{
		AbstractNode* pCur = _pFirstChild;
		while (pCur && pCur->_pNext != oldChild) pCur = pCur->_pNext;
		if (pCur)
		{
			if (doEvents)
			{
				static_cast<AbstractNode*>(oldChild)->dispatchNodeRemoved();
				static_cast<AbstractNode*>(oldChild)->dispatchNodeRemovedFromDocument();
			}
			pCur->_pNext = pCur->_pNext->_pNext;
			static_cast<AbstractNode*>(oldChild)->_pNext   = 0;
			static_cast<AbstractNode*>(oldChild)->_pParent = 0;
		}
		else throw DOMException(DOMException::NOT_FOUND_ERR);
	}
	oldChild->autoRelease();
	if (doEvents) dispatchSubtreeModified();
	return oldChild;
}
