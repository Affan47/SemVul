BERDecodeAndCheck(BufferedTransformation &bt) const
{
	OID oid(bt);
	if (*this != oid)
		BERDecodeError();
}
