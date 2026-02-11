jk_close_socket(jk_sock_t sd, jk_logger_t *l)
{
    int rc;
    int save_errno;

    JK_TRACE_ENTER(l);

    if (!IS_VALID_SOCKET(sd)) {
        JK_TRACE_EXIT(l);
        return -1;
    }

    save_errno = errno;
#if defined(WIN32) || (defined(NETWARE) && defined(__NOVELL_LIBC__))
    rc = closesocket(sd) ? -1 : 0;
#else
    do {
        rc = close(sd);
    } while (JK_IS_SOCKET_ERROR(rc) && (errno == EINTR || errno == EAGAIN));
#endif
    JK_TRACE_EXIT(l);
    errno = save_errno;
    return rc;
}
