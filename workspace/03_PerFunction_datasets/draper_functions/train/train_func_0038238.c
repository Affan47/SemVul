modbus_tcp_pi_accept(modbus_t *ctx, int *s)
{
    struct sockaddr_storage addr;
    socklen_t addrlen;

    if (ctx == NULL) {
        errno = EINVAL;
        return -1;
    }

    addrlen = sizeof(addr);
#ifdef HAVE_ACCEPT4

    ctx->s = accept4(*s, (struct sockaddr *)&addr, &addrlen, SOCK_CLOEXEC);
#else
    ctx->s = accept(*s, (struct sockaddr *)&addr, &addrlen);
#endif
    if (ctx->s == -1) {
        close(*s);
        *s = -1;
    }

    if (ctx->debug) {
        printf("The client connection is accepted.\n");
    }

    return ctx->s;
}
