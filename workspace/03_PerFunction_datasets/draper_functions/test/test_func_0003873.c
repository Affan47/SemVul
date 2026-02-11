shell_command(char *cmd)
{
	FILE *pipe;
	char buf[BUFSIZE];

	if ((pipe = popen(cmd, "r")) == NULL) {
		error(INFO, "cannot open pipe: %s\n", cmd);
		pc->redirect &= ~REDIRECT_SHELL_COMMAND;
                pc->redirect |= REDIRECT_FAILURE;
                return REDIRECT_FAILURE;
        }

        while (fgets(buf, BUFSIZE, pipe))
		fputs(buf, fp);
        pclose(pipe);

	return REDIRECT_SHELL_COMMAND;
}
