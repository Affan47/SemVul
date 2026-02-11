translate_command(struct dag_node *n, char *old_command, int is_local)
{
	char *new_command;
	char *sp;
	char *token;
	int first = 1;
	int wait = 0;
	int padding = 3;
	char prefix;

	UPTRINT_T current_length = (UPTRINT_T) 0;

	for(sp = old_command; *sp; sp++)
		if(isspace((int) *sp))
			padding += 2;

	new_command = malloc((strlen(old_command) + padding) * sizeof(char));
	new_command[0] = '\0';

	token = strtok(old_command, " \t\n");

	while(token) {


		switch (token[0]) {
		case '<':
		case '>':
			prefix = token[0];
			++token;
			break;
		default:
			prefix = '\0';
		}

		if(prefix && !token) {


			wait = 1;
		}

		char *val = NULL;
		int len;

		if(!is_local)
			val = dag_file_remote_name(n, token);

		if(!first) {
			strncat(new_command + current_length, " ", 1);
			++current_length;
		} else {
			first = 0;
		}


		if(prefix) {
			strncat(new_command + current_length, &prefix, 1);
			++current_length;
		}

		if(val) {


			if(wait) {
				wait = 0;
			} else {
				strncat(new_command + current_length, "./", 2);
				current_length += 2;
			}

			len = strlen(val);
			strncat(new_command + current_length, val, len);
			current_length += len;
		} else {
			len = strlen(token);
			strncat(new_command + current_length, token, len);
			current_length += len;
		}

		token = strtok(NULL, " \t\n");
	}

	return new_command;
}
