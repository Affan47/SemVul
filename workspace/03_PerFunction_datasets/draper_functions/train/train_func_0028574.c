setupParse()
{
	poco_check_ptr (_pParent);

	_pParent->setEntityResolver(this);
	_pParent->setDTDHandler(this);
	_pParent->setContentHandler(this);
	_pParent->setErrorHandler(this);
}
