send_ipc_int (int fd, ipc_type type, int val) {
    int len;
    if (fd == -1)
        return;

    len = sizeof(ipc_type) + sizeof(int);
    if (write(fd, &len,  sizeof(int)) <= 0)
     perror("send_ipc_int(): write length:");
    if (write(fd, &type, sizeof(ipc_type)) <= 0)
     perror("send_ipc_int(): write type:");
    if (write(fd, &val,  sizeof(int)) <= 0)
     perror("send_ipc_int(): write value:");
}
