lock_sched() {
    char filename[256];
    char pid_string[16];
    int fd, pid, count;

    g_reply->lockfile_fd=-1;

    sprintf(filename, "%s/CGI_%07d",
        config.sched_lockfile_dir, g_reply->host.id
    );

    fd = open(filename, O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
    if (fd < 0) return -1;


    pid = mylockf(fd);
    if (pid) {
        close(fd);
        return pid;
    }


    count = sprintf(pid_string, "%d\n", getpid());
    ssize_t n = write(fd, pid_string, count);
    if (n < 0) {
        close(fd);
        return -1;
    }
    fsync(fd);

    g_reply->lockfile_fd = fd;
    return 0;
}
