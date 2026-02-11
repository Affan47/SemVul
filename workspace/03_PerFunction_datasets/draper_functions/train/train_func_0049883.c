smtp_auth_var(const char *type, const char *addr)
{
	char	*var, *cp;
	int	len;

	var = ac_alloc(len = strlen(type) + strlen(addr) + 7);
	snprintf(var, len, "smtp-auth%s-%s", type, addr);
	if ((cp = value(var)) != NULL)
		cp = savestr(cp);
	else {
		snprintf(var, len, "smtp-auth%s", type);
		if ((cp = value(var)) != NULL)
			cp = savestr(cp);
	}
	ac_free(var);
	return cp;
}
