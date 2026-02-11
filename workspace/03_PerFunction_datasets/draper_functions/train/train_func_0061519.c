type() const
{
	if(isNull())
		return RSA;
	return static_cast<const PKeyContext *>(context())->key()->type();
}
