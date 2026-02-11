internal_check(char *username)
{
    int length = strlen(username);

    if (!strncmp(username, "version", 7) && length == 7 &&
	prog_config.config_bits3 & SHOW_CONFESSION)
	return(U_INTERNAL);
    else if (!strncmp(username, "help", 4) && length == 4 &&
	prog_config.config_bits3 & SHOW_CONFESSION)
	return(U_INTERNAL);
    else if (!strncmp(username, "services", 8) && length == 8 &&
	     prog_config.config_bits3 & SHOW_FAKEUSER)
	return(U_INTERNAL);
    else if (!strncmp(username, "search", 6) &&
	     prog_config.config_bits2 & SHOW_SEARCHFING)
	return(U_INTERNAL);
    else if (((!strncmp(username, "userlist-only", 13) && length == 13)
	      || (!strncmp(username, "userlist-online", 15) && length == 15))
	     && (prog_config.config_bits2 & SHOW_ULISTONLY) &&
	     ((local_finger && prog_config.local_config_bits2 & SHOW_SYSTEMLIST) ||
	      (!local_finger && prog_config.config_bits2 & SHOW_SYSTEMLIST)))
	return(U_INTERNAL);

    return(0);
}
