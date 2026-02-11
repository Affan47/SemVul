command_is_silent (const CMD *cmd, const char *line)
{
    if (cmd->ci == FUNCERR || cmd->ci == PRINTF ||
	(cmd->ci == PRINT && strchr(line, '"'))) {
	return 1;
    }

    if (!strncmp(line, "quit", 4) && string_is_blank(line + 4)) {
	return 1;
    }

    if (cmd->ci == SET && !strcmp(cmd->param, "echo") &&
	gretl_function_depth() > 0) {
	return 1;
    }

    if (cmd->ci == OUTFILE && cmd->opt == OPT_C) {
	return 1;
    }

    if (*line == '!') {
	return 1;
    }

    return 0;
}
