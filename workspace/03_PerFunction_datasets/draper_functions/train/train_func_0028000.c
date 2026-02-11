signal_handler(int signal)
{
	switch (signal)
	{
		case SIGCHLD:
		{
			int status, exit_status = 0;
			pid_t pid;
			char *name = NULL;

			while ((pid = waitpid(-1, &status, WNOHANG)) > 0)
			{
				if (pid == starter_charon_pid())
				{
					if (asprintf(&name, " (%s)", daemon_name) < 0)
					{
						 name = NULL;
					}
				}
				if (WIFSIGNALED(status))
				{
					DBG2(DBG_APP, "child %d%s has been killed by sig %d\n",
						 pid, name?name:"", WTERMSIG(status));
				}
				else if (WIFSTOPPED(status))
				{
					DBG2(DBG_APP, "child %d%s has been stopped by sig %d\n",
						 pid, name?name:"", WSTOPSIG(status));
				}
				else if (WIFEXITED(status))
				{
					exit_status =  WEXITSTATUS(status);
					if (exit_status >= SS_RC_FIRST && exit_status <= SS_RC_LAST)
					{
						_action_ =  FLAG_ACTION_QUIT;
					}
					DBG2(DBG_APP, "child %d%s has quit (exit code %d)\n",
						 pid, name?name:"", exit_status);
				}
				else
				{
					DBG2(DBG_APP, "child %d%s has quit", pid, name?name:"");
				}
				if (pid == starter_charon_pid())
				{
					starter_charon_sigchild(pid, exit_status);
				}
			}

			if (name)
			{
				free(name);
			}
		}
		break;

		case SIGALRM:
			_action_ |= FLAG_ACTION_START_CHARON;
			break;

		case SIGHUP:
			_action_ |= FLAG_ACTION_UPDATE;
			break;

		case SIGTERM:
		case SIGQUIT:
		case SIGINT:
			_action_ |= FLAG_ACTION_QUIT;
			break;

		case SIGUSR1:
			_action_ |= FLAG_ACTION_RELOAD;
			_action_ |= FLAG_ACTION_UPDATE;
			break;

		default:
			DBG1(DBG_APP, "fsig(): unknown signal %d -- investigate", signal);
			break;
	}
}
