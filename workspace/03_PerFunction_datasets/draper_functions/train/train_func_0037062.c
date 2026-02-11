_start_process(const char *name,
                          int (*proc_func)(FILE *, FILE *, void *),
                          void *user_arg, FILE **pipe_in, FILE **pipe_out,
                          int createprocessgroup)
{
    pid_t pid;
    int pfdin[2], pfdout[2];
    int ret;
    FILE *in, *out;

    if (pipe_in)
      if (pipe(pfdin) < 0)
	return -1;
    if (pipe_out)
      if (pipe(pfdout) < 0)
	return -1;

    _log("Starting process \"%s\" (generation %d)\n", name, kidgeneration +1);

    pid = fork();
    if (pid < 0) {
        _log("Could not fork for %s\n", name);
        if (pipe_in) {
            close(pfdin[0]);
            close(pfdin[1]);
        }
        if (pipe_out) {
            close(pfdout[0]);
            close(pfdout[1]);
        }
        return -1;
    }

    if (pid == 0) {
        if (pipe_in) {
            close(pfdin[1]);
            in = fdopen(pfdin[0], "r");
        }
        else
            in = NULL;

        if (pipe_out) {
            close(pfdout[0]);
            out = fdopen(pfdout[1], "w");
        }
        else
            out = NULL;

        if (createprocessgroup)
            setpgid(0, 0);

        kidgeneration++;


        clear_proc_list();

        ret = proc_func(in, out, user_arg);
        exit(ret);
    }


    if (pipe_in) {
        close(pfdin[0]);
        *pipe_in = fdopen(pfdin[1], "w");
        if (!*pipe_in)
            _log("fdopen: %s\n", strerror(errno));
    }
    if (pipe_out) {
        close(pfdout[1]);
        *pipe_out = fdopen(pfdout[0], "r");
        if (!*pipe_out)
            _log("fdopen: %s\n", strerror(errno));
    }


    add_process(name, pid, createprocessgroup);

    return pid;
}
