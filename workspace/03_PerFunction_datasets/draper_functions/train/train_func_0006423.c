cmd_run(struct token_t *command, struct llist_t *arglist, int bg)
{


	struct llist_t *iter = arglist;
	if (ShowTokens) {
		PrintToken(RUN, "run", "run");
		PrintToken(command->ttype, command->value, "cmd");
		int count = 0;
		char argN[] = "arg 0000";
		if(iter != NULL)
			ll_foreach(iter, {
				count++;
				sprintf(argN, "arg %4d",  count);
				PrintToken(iter->value->ttype, iter->value->value, argN);
			});
		if(bg)
			PrintToken(BG, "<bg>", "background");
	}
	var_value(command);
	iter = arglist;
	if(iter != NULL)
		ll_foreach(iter, {
			var_value(iter->value);
		});
	if (bg) {
		pid_t pid = fork();
		if (pid == 0) {

			char ** nargv = create_arglist(command, arglist);
			int retval = execvp(nargv[0],nargv);
			if(retval == -1)
				printf("%s\n", strerror(errno));
			exit(0);
		}
		else {


			char *cmd_cpy = strdup(command->value);
			struct pidlist_t *pidnode = malloc(sizeof(struct pidlist_t));
			pidnode->pid = pid;
			pidnode->name = cmd_cpy;
			pidnode->next = bg_procs;
			bg_procs = pidnode;

		}
	}
	else {
		pid_t pid = fork();
		if (pid == 0) {
			char ** nargv = create_arglist(command, arglist);
			int retval = execvp(nargv[0],nargv);
			if(retval == -1)
				printf("%s\n", strerror(errno));
			exit(0);
		}
		else {
			int errormsg = 0;
			pid_t child = wait(&errormsg);


		}
	}

	tk_free(command);
	ll_free(arglist);
}
