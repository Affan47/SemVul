automode(char const *arg, command_t *cmd)
{
	if (cmd->mode != MODE_UNKNOWN) return arg;

	if (!strcmp(arg, "CC") ||
	    !strcmp(arg, "CXX")) {
		DEBUG("Now in compile mode, guessed from: %s\n", arg);
		arg = CC;
		cmd->mode = MODE_COMPILE;

	} else if (!strcmp(arg, "LINK") ||
		   !strcmp(arg, "LINK.c") ||
		   !strcmp(arg, "LINK.cxx")) {
		DEBUG("Now in linker mode, guessed from: %s\n", arg);
		arg = LINK_C;
		cmd->mode = MODE_LINK;
	}

	return arg;
}
