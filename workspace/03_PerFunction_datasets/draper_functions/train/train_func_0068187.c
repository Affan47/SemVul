command_I(command, argument)
    char *command;
    char *argument;
{
    char message[MAX_STRING_LENGTH + 1];
    EB_Position position;


    if (*argument != '\0') {
	syslog(LOG_INFO, "too many arguments: command=%s, host=%s(%s)",
	    command, client_host_name, client_address);
	if (write_string_all(accepted_out_file, idle_timeout, "$?\n") <= 0)
	    return -1;
	return 0;
    }


    if (current_book == NULL) {
	syslog(LOG_INFO, "no current book: command=%s, host=%s(%s)",
	    command, client_host_name, client_address);
	if (write_string_all(accepted_out_file, idle_timeout, "$<\n") <= 0)
	    return -1;
	return 0;
    }


    if (write_string_all(accepted_out_file, idle_timeout, "$I\n") <= 0)
	return -1;
    if (eb_have_word_search(&current_book->book)) {
	if (write_string_all(accepted_out_file, idle_timeout, "IA 1\nIK 1\n")
	    <= 0)
	    return -1;
    }
    if (eb_have_endword_search(&current_book->book)) {
	if (write_string_all(accepted_out_file, idle_timeout, "BA 1\nBK 1\n")
	    <= 0)
	    return -1;
    }
    if (eb_menu(&current_book->book, &position) == EB_SUCCESS) {
	sprintf(message, "HA %x\n", position.page);
	if (write_string_all(accepted_out_file, idle_timeout, message) <= 0)
	    return -1;
    }
    if (eb_copyright(&current_book->book, &position) == EB_SUCCESS) {
	sprintf(message, "OK %x\n", position.page);
	if (write_string_all(accepted_out_file, idle_timeout, message) <= 0)
	    return -1;
    }
    if (eb_have_keyword_search(&current_book->book)) {
	if (write_string_all(accepted_out_file, idle_timeout, "JO 1\n") <= 0)
	    return -1;
    }

    if (write_string_all(accepted_out_file, idle_timeout, "$$\n") <= 0)
	return -1;

    syslog(LOG_INFO, "succeeded: command=%s, book=%s/%s, host=%s(%s)",
	command, current_book->name, current_subbook_name, client_host_name,
	client_address);
    return 0;
}
