previousNode()
{
	if (!_pRoot) throw DOMException(DOMException::INVALID_STATE_ERR);

	if (_pCurrent)
		_pCurrent = previous();
	else
		_pCurrent = last();
	while (_pCurrent && !accept(_pCurrent))
		_pCurrent = previous();
	return _pCurrent;
}
