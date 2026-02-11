m_parse(char *cmd_line, int n_fields, char **value)
{
	int field_number;
	char *token;

	token = strtok(0, " 	\n");
	if (token == 0) {
		fputs("Please enter: field-number value > ", stdout);
		fgets(cmd_line, 80, stdin);
		token = strtok(cmd_line, " 	\n");
		if (token == 0)
			return 0;
	}
	field_number = strtol(token, 0, 0);
	if (field_number < 1 || field_number > n_fields) {
		fputs("Invalid field number\n", stderr);
		return 0;
	}
	*value = strtok(0, " 	\n");
	if (*value == 0) {
		fputs("Not enough arguments\n", stderr);
		return 0;
	}
	if (strtok(0, " 	\n")) {
		fputs("Too many arguments\n", stderr);
		return 0;
	}
	return field_number;
}
