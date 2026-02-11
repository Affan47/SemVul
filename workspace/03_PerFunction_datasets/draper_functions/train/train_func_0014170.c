fwdConnectIdleTimeout(int fd, void *data)
{
    idleconn *idle = data;
    debug(17, 2) ("fwdConnectIdleTimeout: FD %d: '%s'\n", fd, idle->peer->name);
    idle->peer->stats.idle_opening--;
    comm_close(fd);
    cbdataFree(idle);
}
