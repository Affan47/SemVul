accept_blocking(void *data)
{
    struct accept_arg *arg = data;
    int ret;
    socklen_t len0 = 0;
    if (arg->len) len0 = *arg->len;
    ret = accept(arg->fd, arg->sockaddr, arg->len);
    if (arg->len && len0 < *arg->len) *arg->len = len0;
    return (VALUE)ret;
}
