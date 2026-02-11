prepare_pipes (CutProcess *process)
{
    CutProcessPrivate *priv = CUT_PROCESS_GET_PRIVATE(process);
    pid_t pid;
    int fork_errno = 0;
    int stdout_pipe[2];
    int stderr_pipe[2];
    int cutter_pipe[2];

    priv->pid = 0;

    if (pipe(stdout_pipe) < 0 ||
        pipe(stderr_pipe) < 0 ||
        pipe(cutter_pipe) < 0) {
        return -1;
    }

    pid = fork();
    if (pid == -1)
        fork_errno = errno;

    if (pid == 0) {
        cut_utils_close_pipe(stdout_pipe, CUT_READ);
        cut_utils_close_pipe(stderr_pipe, CUT_READ);
        cut_utils_close_pipe(cutter_pipe, CUT_READ);

        if (sane_dup2(stdout_pipe[CUT_WRITE], STDOUT_FILENO) < 0 ||
            sane_dup2(stderr_pipe[CUT_WRITE], STDERR_FILENO) < 0) {
        }

        priv->child_io = create_write_io_channel(cutter_pipe[CUT_WRITE]);

        if (stdout_pipe[CUT_WRITE] >= 3)
            cut_utils_close_pipe(stdout_pipe, CUT_WRITE);
        if (stderr_pipe[CUT_WRITE] >= 3)
            cut_utils_close_pipe(stderr_pipe, CUT_WRITE);
    } else {
        priv->pid = pid;

        cut_utils_close_pipe(stdout_pipe, CUT_WRITE);
        cut_utils_close_pipe(stderr_pipe, CUT_WRITE);
        cut_utils_close_pipe(cutter_pipe, CUT_WRITE);

        priv->parent_io = create_read_io_channel(cutter_pipe[CUT_READ]);
        priv->stdout_read_io = create_read_io_channel(stdout_pipe[CUT_READ]);
        priv->stderr_read_io = create_read_io_channel(stderr_pipe[CUT_READ]);
    }

    errno = fork_errno;
    return pid;
}
