code() const
{
	return originalCode ? originalCode : Private::errorTypeCondToCode(type, condition);
}
