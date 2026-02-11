privsep_sendcmd(const int psfd, const void * const cmdarg,
                           const size_t cmdarg_len)
{
    ssize_t sent;

    while ((sent = send(psfd, cmdarg, cmdarg_len, 0)) == (ssize_t) -1 &&
           errno == EINTR);
    if (sent != (ssize_t) cmdarg_len) {
        return -1;
    }
    return 0;
}
