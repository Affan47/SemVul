get_hash_id(const QString &name)
{
	if(name == "sha1")
		return QByteArray::fromRawData((const char *)pkcs_sha1, sizeof(pkcs_sha1));
	else if(name == "md5")
		return QByteArray::fromRawData((const char *)pkcs_md5, sizeof(pkcs_md5));
	else if(name == "md2")
		return QByteArray::fromRawData((const char *)pkcs_md2, sizeof(pkcs_md2));
	else if(name == "ripemd160")
		return QByteArray::fromRawData((const char *)pkcs_ripemd160, sizeof(pkcs_ripemd160));
	else
		return QByteArray();
}
