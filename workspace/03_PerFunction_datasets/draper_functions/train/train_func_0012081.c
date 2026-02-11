lookup_action(const char *str, int *act)
{
	if (strcmp(str, "never") == 0)
		*act = AUDIT_NEVER;
	else if (strcmp(str, "possible") == 0)
		return 1;
	else if (strcmp(str, "always") == 0)
		*act = AUDIT_ALWAYS;
	else
		return 2;
	return 0;
}
