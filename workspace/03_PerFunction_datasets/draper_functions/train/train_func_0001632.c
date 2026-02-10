init_pipe_struct_pair(struct pipe_struct *read_pipe, struct pipe_struct *write_pipe)
{
    int retval;
    int pipefds[2];

    retval = pipe(pipefds);
    if (retval < 0) {
        perror("Unable to create a new pipe!");
	goto out;
    }

    read_pipe->pipe_fd       = pipefds[0];
    read_pipe->pipe_mate_fd  = pipefds[1];
    write_pipe->pipe_fd      = pipefds[1];
    write_pipe->pipe_mate_fd = pipefds[0];

    retval = update_pipe_struct(read_pipe);
    if (retval < 0) {
        goto out;
    }
    retval = update_pipe_struct(write_pipe);

out:
    return retval;
}
