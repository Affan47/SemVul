operator==(const CertificateInfoPair &other) const
{
	if(d->type == other.d->type && d->value == other.d->value)
		return true;
	return false;
}
