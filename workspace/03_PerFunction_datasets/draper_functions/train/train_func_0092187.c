pty_pair_create(void)
{
    int val;
    static char local_slavename[SLAVE_SIZE];
    pty_pair_ptr ptr = (pty_pair_ptr) cgdb_malloc(sizeof (struct pty_pair));

    if (!ptr)
        return NULL;

    ptr->masterfd = -1;
    ptr->slavefd = -1;
    ptr->slavename[0] = 0;

    val = pty_open(&(ptr->masterfd), &(ptr->slavefd), local_slavename,
            SLAVE_SIZE, NULL, NULL);
    if (val == -1) {
        logger_write_pos(logger, __FILE__, __LINE__, "PTY open");
        return NULL;
    }

    strncpy(ptr->slavename, local_slavename, SLAVE_SIZE);

    return ptr;
}
