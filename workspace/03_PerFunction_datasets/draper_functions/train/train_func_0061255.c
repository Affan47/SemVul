command_v(command, argument)
    char *command;
    char *argument;
{
    char message[MAX_STRING_LENGTH + 1];


    if (*argument != '\0') {
	syslog(LOG_INFO, "too many arguments: command=%s, host=%s(%s)",
	    command, client_host_name, client_address);
	if (write_string_all(accepted_out_file, idle_timeout, "$?\n") <= 0)
	    return -1;
	return 0;
    }

    sprintf(message, "$v%s version %s\n", program_name, program_version);
    if (write_string_all(accepted_out_file, idle_timeout, message) <= 0)
	return -1;

    syslog(LOG_INFO, "succeeded: command=%s, host=%s(%s)",
	command, client_host_name, client_address);
    return 0;
}
