subjectPublicKey() const
{
	PKeyContext *c = static_cast<const CSRContext *>(context())->subjectPublicKey();
	PublicKey key;
	key.change(c);
	return key;
}
