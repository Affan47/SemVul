sigar_net_connection_walk(sigar_net_connection_walker_t *walker)
{
    int flags = walker->flags;
    int status;

    if (flags & SIGAR_NETCONN_TCP) {
        status = proc_net_read(walker,
                               PROC_FS_ROOT "net/tcp",
                               SIGAR_NETCONN_TCP);

        if (status != SIGAR_OK) {
            return status;
        }

        status = proc_net_read(walker,
                               PROC_FS_ROOT "net/tcp6",
                               SIGAR_NETCONN_TCP);

        if (!((status == SIGAR_OK) || (status == ENOENT))) {
            return status;
        }
    }

    if (flags & SIGAR_NETCONN_UDP) {
        status = proc_net_read(walker,
                               PROC_FS_ROOT "net/udp",
                               SIGAR_NETCONN_UDP);

        if (status != SIGAR_OK) {
            return status;
        }

        status = proc_net_read(walker,
                               PROC_FS_ROOT "net/udp6",
                               SIGAR_NETCONN_UDP);

        if (!((status == SIGAR_OK) || (status == ENOENT))) {
            return status;
        }
    }

    if (flags & SIGAR_NETCONN_RAW) {
        status = proc_net_read(walker,
                               PROC_FS_ROOT "net/raw",
                               SIGAR_NETCONN_RAW);

        if (status != SIGAR_OK) {
            return status;
        }

        status = proc_net_read(walker,
                               PROC_FS_ROOT "net/raw6",
                               SIGAR_NETCONN_RAW);

        if (!((status == SIGAR_OK) || (status == ENOENT))) {
            return status;
        }
    }


    return SIGAR_OK;
}
