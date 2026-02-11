GB_SystemDomainName(void)
{
	char host[256], domain[256];

	if (gethostname(host, sizeof(host) - 1))
		return "";

	if (getdomainname(domain, sizeof(domain) - 1))
		return "";

	if ((strlen(host) + strlen(domain)) > COMMON_BUF_MAX)
		return "";

	*COMMON_buffer = 0;
	if (*domain && strcmp(domain, "(none)"))
	{
		strcpy(COMMON_buffer, domain);
		strcat(COMMON_buffer, ".");
	}
	strcat(COMMON_buffer, host);

	return COMMON_buffer;
}
