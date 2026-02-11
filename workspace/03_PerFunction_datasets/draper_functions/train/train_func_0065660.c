rl_set_prompt(const char *prompt)
{
	char *p;

	if (!prompt)
		prompt = "";
	if (rl_prompt != NULL && strcmp(rl_prompt, prompt) == 0)
		return 0;
	if (rl_prompt)
		el_free(rl_prompt);
	rl_prompt = strdup(prompt);
	if (rl_prompt == NULL)
		return -1;

	while ((p = strchr(rl_prompt, RL_PROMPT_END_IGNORE)) != NULL)
		*p = RL_PROMPT_START_IGNORE;

	return 0;
}
