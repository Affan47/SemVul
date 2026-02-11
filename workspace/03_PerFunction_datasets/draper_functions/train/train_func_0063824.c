dotconf_command_loop_until_error(configfile_t *configfile)
{
	char buffer[CFG_BUFSIZE];

	while ( !(dotconf_get_next_line(buffer, CFG_BUFSIZE, configfile)) )
	{
		const char *error = dotconf_handle_command(configfile, buffer);
		if ( error )
			return error;
	}
	return NULL;
}
