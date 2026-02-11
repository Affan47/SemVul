exec
	(
	const char *file,
	char *argv[],
	Reader_fun rfun,
	void *udata
	)
	{
	reader = rfun;
	reader_data = udata;

	int stdin_pipe[2], stdout_pipe[2], stderr_pipe[2];
	stdin_pipe[0] = stdin_pipe[1] = stdout_pipe[0] = stdout_pipe[1] =
	stderr_pipe[0] = stderr_pipe[1] = -1;
	kill_child();

	if (pipe(stdin_pipe) != 0 || pipe(stdout_pipe) != 0 ||
	    pipe(stderr_pipe) != 0)
		{
		Close_pipes(stdin_pipe, stdout_pipe, stderr_pipe);
		return false;
		}
	child_pid = fork();
	if (child_pid == -1)
		{
		Close_pipes(stdin_pipe, stdout_pipe, stderr_pipe);
		return false;
		}
	if (child_pid == 0)
		{
		close(0);
		dup(stdin_pipe[0]);
		Close_pipe(stdin_pipe);
		close(1);
		dup(stdout_pipe[1]);
		Close_pipe(stdout_pipe);
		close(2);
		dup(stderr_pipe[1]);
		Close_pipe(stderr_pipe);
		execvp(file, argv);
		exit(-1);
		}

	child_stdin = stdin_pipe[1];
	close(stdin_pipe[0]);
	child_stdout = stdout_pipe[0];
	close(stdout_pipe[1]);
	child_stderr = stderr_pipe[0];
	close(stderr_pipe[1]);
cout << "Child_stdout is " << child_stdout << ", Child_stderr is " <<
		child_stderr << endl;
	stdout_tag = gdk_input_add(child_stdout,
			GDK_INPUT_READ, Read_from_child, this);
	stderr_tag = gdk_input_add(child_stderr,
			GDK_INPUT_READ, Read_from_child, this);
	return true;
	}
