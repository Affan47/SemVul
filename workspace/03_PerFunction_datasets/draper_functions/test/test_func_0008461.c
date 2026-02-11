main(void)
{

	char line[BUFFERSIZE];

	char * cmd[BUFFERSIZE];

	int user_exit = 0;

	int interactive = 0;

	int offset = 0;

	pid_t childpid;


	while (!user_exit)
	{

		printf("> ");


		read_line(line);
		parse(line, cmd);


		user_exit = ((strcmp(cmd[0], "exit")) == 0);
		if (user_exit) continue;


		if (strcmp(cmd[0], "pola-i") == 0 && cmd[1] != NULL)
		{
			interactive = 1;
			setenv("POLA_I", "true", 1);

			offset = strlen(cmd[0])+strlen(cmd[1]);
		}
		else
		{
			interactive = 0;
			setenv("POLA_I", "false", 1);

			offset = strlen(cmd[0]);
		}


		if (cmd[0][0] != '\0')
		{

			childpid = fork();
			switch (childpid)
			{
				case -1:
					perror("fork: ");
					exit(-1);


				case 0:

					setenv("LD_PRELOAD", LIBPATH, 1);

					setenv("POLA_CMD", (line + offset + 1), 1);

					if (interactive)
					{
						execvp(cmd[1], &(cmd[1]));
					}
					else
					{
						execvp(cmd[0], cmd);
					}
					perror("execvp: ");
					exit(-2);


				default :
					waitpid(childpid, NULL, 0);
			}
		}

	}

	return 0;
}
