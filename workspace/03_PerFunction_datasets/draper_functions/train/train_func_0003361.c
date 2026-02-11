moveMapValues(CertificateInfo *from, CertificateInfoOrdered *to, const CertificateInfoType &type)
{
	QList<QString> values = from->values(type);
	from->remove(type);


	for(int n = values.count() - 1; n >= 0; --n)
		to->append(CertificateInfoPair(type, values[n]));
}
