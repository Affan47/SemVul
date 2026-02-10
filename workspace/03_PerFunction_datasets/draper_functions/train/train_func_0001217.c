set_default_email_from(conf_data_t * data)
{
	struct passwd *pwd = NULL;
	char *hostname = NULL;
	int len = 0;

	hostname = get_local_name();
	if (!hostname || !hostname[0])
		return;

	pwd = getpwuid(getuid());
	if (!pwd)
		return;

	len = strlen(hostname) + strlen(pwd->pw_name) + 2;
	data->email_from = MALLOC(len);
	if (!data->email_from)
		return;

	snprintf(data->email_from, len, "%s@%s", pwd->pw_name, hostname);
}
