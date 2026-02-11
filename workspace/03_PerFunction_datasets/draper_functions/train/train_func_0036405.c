update_user_time(char *tty)
{
	struct information *current_info = &info;
	char temp[BUFLEN] = "";

	if (current_info->users.ctime == NULL) {
		current_info->users.ctime = malloc(text_buffer_size);
	}

	tty_user_time(temp, tty);

	if (temp != NULL) {
		if (current_info->users.ctime) {
			free(current_info->users.ctime);
			current_info->users.ctime = 0;
		}
		current_info->users.ctime = malloc(text_buffer_size);
		strncpy(current_info->users.ctime, temp, text_buffer_size);
	} else {
		if (current_info->users.ctime) {
			free(current_info->users.ctime);
			current_info->users.ctime = 0;
		}
		current_info->users.ctime = malloc(text_buffer_size);
		strncpy(current_info->users.ctime, "broken", text_buffer_size);
	}
}
