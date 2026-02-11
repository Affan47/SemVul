smtpauthed(const char *login) {
    if(skipauth && !cli_regexec(&authreg, login, 0, NULL, 0))
	return 1;
    return 0;
}
