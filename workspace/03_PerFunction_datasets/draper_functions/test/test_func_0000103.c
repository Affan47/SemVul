explain_buffer_errno_getsockname_explanation(explain_string_buffer_t *sb,
    int errnum, int fildes, struct sockaddr *sock_addr,
    socklen_t *sock_addr_size)
{


    (void)sock_addr;
    switch (errnum)
    {
    case EBADF:
        explain_buffer_ebadf(sb, fildes, "fildes");
        break;

    case EFAULT:
        if (explain_is_efault_pointer(sock_addr_size, sizeof(*sock_addr_size)))
            explain_buffer_efault(sb, "sock_addr_size");
        else
            explain_buffer_efault(sb, "sock_addr");
        break;

    case EINVAL:
        if
        (
            explain_is_efault_pointer
            (
                sock_addr_size,
                sizeof(*sock_addr_size)
            )
        )
            goto dunno;
        explain_buffer_einval_too_small
        (
            sb,
            "sock_addr_size",
            (int)*sock_addr_size
        );
        break;

    case ENOBUFS:
        explain_buffer_enobufs(sb);
        break;

    case ENOTCONN:
        explain_buffer_enotconn(sb, "fildes");
        break;

    case ENOTSOCK:
        explain_buffer_enotsock(sb, fildes, "fildes");
        break;

    default:
        dunno:
        explain_buffer_errno_generic(sb, errnum, "getsockname");
        break;
    }
}
