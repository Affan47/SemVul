username_completion_function(const char *text, int state)
{
	struct passwd *pwd;

	if (text[0] == '\0')
		return (NULL);

	if (*text == '~')
		text++;

	if (state == 0)
		setpwent();

   while ((pwd = getpwent())
		&& pwd != NULL && text[0] == pwd->pw_name[0]
		&& strcmp(text, pwd->pw_name) == 0);

	if (pwd == NULL) {
		endpwent();
		return NULL;
	}
	return strdup(pwd->pw_name);
}
