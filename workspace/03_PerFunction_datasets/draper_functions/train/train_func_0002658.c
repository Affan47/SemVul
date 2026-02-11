sync_wait_simple(int fd, sync_type_t type)
{
    sync_msg_t msg;

    sync_wait(fd, &msg);
    if (msg.type == SYNC_ABORT) {
        fprintf(stderr, "Abort signalled while doing child synchronization.\n");
        exit(EXIT_FAILURE);
    }
    EXPECT(msg.type == type);
}
