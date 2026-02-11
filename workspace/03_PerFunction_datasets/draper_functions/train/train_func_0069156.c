set_environment_variables (apr_pool_t *pool, char *environment_variables)
{
	char *tmp;
	char *name;
	char *value;


	if (environment_variables == NULL)
		return;

	name = environment_variables;
	tmp = strchr (environment_variables, '=');
	while (tmp != NULL) {
		*tmp = '\0';
		value = tmp + 1;
		tmp = strchr (value, ';');
		if (tmp != NULL)
			*tmp = '\0';

		SETENV (pool, name, value);
		if (tmp == NULL)
			break;

		name = tmp + 1;
		tmp = strchr (name, '=');
	}
}
