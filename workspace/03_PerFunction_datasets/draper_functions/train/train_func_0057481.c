prompt_for_password(const char *username)
{
	char	   *result;

	if (username == NULL)
		result = simple_prompt("Password: ", 100, false);
	else
	{
		char	   *prompt_text;

		prompt_text = malloc(strlen(username) + 32);
		sprintf(prompt_text, "Password for user \"%s\": ", username);
		result = simple_prompt(prompt_text, 100, false);
		free(prompt_text);
	}

	return result;
}
