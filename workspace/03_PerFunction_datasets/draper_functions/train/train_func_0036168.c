parse_command_line(char *cmd, ProgramMode *mode,
                              LHAOptions *options)
{


	if (*cmd == '-') {
		++cmd;
	}

	*mode = mode_for_char(*cmd);

	if (*mode == MODE_UNKNOWN) {
		return 0;
	}


	if (!parse_options(cmd + 1, options)) {
		return 0;
	}

	return 1;
}
