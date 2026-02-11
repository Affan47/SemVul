var_eval(char *orig, int len, char *dest, int max_len)
{
	char var[VAR_LENGTH + 1];
	char storage[64 * 5];
	float multiplier;
	int type = 0;
	void *p;
	int nb = 0;
	memset(var, 0, sizeof(var));
	strncpy(var, orig + 1, len - 1);
	p = get_var_address(var, &multiplier, &type, storage, sizeof(storage));
	if (p)
		nb = snprintf_pointer(dest, max_len, type, p, multiplier);
	return nb;
}
