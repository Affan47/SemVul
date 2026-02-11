privsep_sendfd(const int psfd, const int fd)
{
    char *buf;
    int *fdptr;
    struct cmsghdr *cmsg;
    struct msghdr msg;
    struct iovec vec;
    const size_t sizeof_buf = CMSG_SPACE(sizeof *fdptr);
    size_t sizeof_buf_ = sizeof_buf;
    PrivSepCmd fodder = PRIVSEPCMD_ANSWER_FD;
    ssize_t sent;

    if (sizeof_buf_ < sizeof *cmsg) {
        sizeof_buf_ = sizeof *cmsg;
    }
    if ((buf = ALLOCA(sizeof_buf_)) == NULL) {
        return -1;
    }
    memset(&msg, 0, sizeof msg);
    vec.iov_base = (void *) &fodder;
    vec.iov_len = sizeof fodder;
    msg.msg_name = NULL;
    msg.msg_namelen = (socklen_t) 0;
    msg.msg_iov = &vec;
    msg.msg_iovlen = (size_t) 1U;
    msg.msg_control = buf;
    msg.msg_controllen = sizeof_buf;
    msg.msg_flags = 0;
    if ((cmsg = CMSG_FIRSTHDR(&msg)) == NULL) {
        ALLOCA_FREE(buf);
        return -1;
    }
    cmsg->cmsg_len = CMSG_LEN(sizeof fd);
    cmsg->cmsg_level = SOL_SOCKET;
    cmsg->cmsg_type = SCM_RIGHTS;
    if ((fdptr = (int *) (void *) CMSG_DATA(cmsg)) == NULL) {
        ALLOCA_FREE(buf);
        return -1;
    }
    *fdptr = fd;
    msg.msg_controllen = cmsg->cmsg_len;
    while ((sent = sendmsg(psfd, &msg, 0)) == (ssize_t) -1 && errno == EINTR);
    ALLOCA_FREE(buf);
    if (sent != (ssize_t) sizeof fodder) {
        return -1;
    }
    return 0;
}
