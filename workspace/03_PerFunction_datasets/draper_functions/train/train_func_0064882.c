keyNameIsSystem(const char *keyName)
{
	if (!strncmp("system",keyName,sizeof("system")-1)) return 1;
	return 0;
}
