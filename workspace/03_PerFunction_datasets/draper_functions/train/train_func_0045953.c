parse_argument(const char argument[], PROCEDURE* procedure)
{
	const char *s = strchr(argument, '.');

	if (s) {
		size_t len = s - argument;
		if (len > sizeof(procedure->owner) - 1)
			len = sizeof(procedure->owner) - 1;
		memcpy(procedure->owner, argument, len);
		procedure->owner[len] = '\0';

		tds_strlcpy(procedure->name, s+1, sizeof(procedure->name));
	} else {
		strcpy(procedure->owner, "dbo");
		tds_strlcpy(procedure->name, argument, sizeof(procedure->name));
	}
}
