validator(Validator* pValidator)
{
	if (_pValidator) _pValidator->release();
	_pValidator = pValidator;
	return *this;
}
