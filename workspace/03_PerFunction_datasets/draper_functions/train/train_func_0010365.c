fromPEM(const QString &s, const SecureArray &passphrase, ConvertResult *result, const QString &provider)
{
	return get_privatekey_pem(s, QString(), (void *)&s, passphrase, result, provider);
}
