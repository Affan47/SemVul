request_input_string_return(char *input)
{
	int i;

	for (i = 0; agent_input[i].attribute != NULL; i++) {
		if (agent_input[i].requested == true) {
			request_input_append(agent_input[i].attribute, input);
			agent_input[i].requested = false;
			break;
		}
	}

	request_input_next();
}
