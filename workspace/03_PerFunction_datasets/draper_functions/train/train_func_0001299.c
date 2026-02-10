isLUKS(const char *type)
{
	return (type && !strcmp(CRYPT_LUKS1, type));
}
