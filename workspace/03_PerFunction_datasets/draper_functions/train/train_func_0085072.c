add_more_loop_commands (LOOPSET *loop)
{
    int nb = 1 + (loop->n_cmds + 1) / LOOP_BLOCK;
    int totcmds = nb * LOOP_BLOCK;
    loop_command *cmds;


    cmds = realloc(loop->cmds, totcmds * sizeof *cmds);

    if (cmds == NULL) {
	return E_ALLOC;
    }

    loop->cmds = cmds;
    loop_cmds_init(loop, loop->n_cmds, totcmds);

    return 0;
}
