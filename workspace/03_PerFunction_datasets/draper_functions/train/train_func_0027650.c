cloexec(int fd) {
    int fdflags;

    fdflags = fcntl(fd, F_GETFD);
    if (fdflags == -1) return -1;
    return fcntl(fd, F_SETFD, fdflags | FD_CLOEXEC);
}
