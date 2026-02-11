LocalPlay(string in_player, string key) {
	vector<string> args;
	char **eargv;

	pid_t sndpid;
	int status;

	args = QuoteStrTokenize(in_player, " ");

	eargv = (char **) malloc(sizeof(char *) * (args.size() + 2));

	for (unsigned int x = 0; x < args.size(); x++) {
		eargv[x] = strdup(args[x].c_str());
	}
	eargv[args.size()] = strdup(key.c_str());
	eargv[args.size() + 1] = NULL;

	if ((sndpid = fork()) == 0) {
		dup2(nulfd, 1);
		dup2(nulfd, 2);
		execvp(eargv[0], eargv);
		exit(1);
	}

	for (unsigned int x = 0; x < args.size() + 2; x++)
		free(eargv[x]);
	free(eargv);

	time_t play_start = time(0);


	while (1) {
		if (waitpid(sndpid, &status, WNOHANG) == 0) {
			if ((time(0) - play_start) > 5) {
				kill(sndpid, SIGKILL);
				continue;
			}

			usleep(10000);
		} else {
			break;
		}
	}

	return 1;
}
