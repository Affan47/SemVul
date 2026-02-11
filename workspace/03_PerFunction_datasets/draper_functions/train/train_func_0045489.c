disable_method(const char *method)
{
	int i;
	bool result = false;

	debug("Disabling method %s\n", method ? method : "ALL");

	for (i = 0; i < ARRAY_SIZE(methods); i++) {

		if (method && strcmp(methods[i].name, method))
			continue;
		if (!methods[i].enabled)
			continue;
		if (methods[i].active)
			methods[i].finish(methods[i].fd);

		methods[i].active = false;
		methods[i].fd = -1;
		methods[i].enabled = false;
		result = true;
	}

	return result;
}
