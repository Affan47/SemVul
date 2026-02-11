explain_buffer_errno_connect_explanation(explain_string_buffer_t *sb,
    int errnum, int fildes, const struct sockaddr *serv_addr,
    int serv_addr_size)
{


    (void)serv_addr_size;
    switch (errnum)
    {
    case EACCES:
        if (serv_addr->sa_family == AF_UNIX)
        {
            const struct sockaddr_un *saddr;
            explain_final_t final_component;

            saddr = (const struct sockaddr_un *)serv_addr;
            explain_final_init(&final_component);
            final_component.want_to_write = 1;
            final_component.must_be_a_st_mode = 1;
            final_component.st_mode = S_IFSOCK;
            final_component.path_max = sizeof(saddr->sun_path) - 1;
            explain_buffer_eacces
            (
                sb,
                saddr->sun_path,
                "sock_addr",
                &final_component
            );
            break;
        }


    case EPERM:
        explain_buffer_gettext
        (
            sb,


            i18n("the process tried to connect to a broadcast address "
            "without having the socket broadcast flag enabled; or, the "
            "connection request failed because of a local firewall "
            "rule")
        );
        break;

    case EADDRINUSE:
        explain_buffer_eaddrinuse(sb, fildes);
        break;

    case EAFNOSUPPORT:
        explain_buffer_eafnosupport
        (
            sb,
            fildes,
            "fildes",
            serv_addr,
            "serv_addr"
        );
        break;

    case EAGAIN:
        explain_buffer_gettext
        (
            sb,


            i18n("no more free local ports or insufficient entries in the "
            "routing cache")
        );
#ifdef __linux__
        if
        (
            serv_addr->sa_family == PF_INET
        &&
            explain_option_dialect_specific()
        )
        {
            explain_string_buffer_puts(sb->footnotes, "; ");
            explain_buffer_gettext
            (
                sb->footnotes,


                i18n("see the net.ipv4.ip_local_port_range sysctl in ip(7) "
                "for how to increase the number of local ports")
            );
        }
#endif
        break;

    case EALREADY:
        explain_buffer_gettext
        (
            sb,


            i18n("the socket is non-blocking and a previous connection "
            "attempt has not yet been completed")
        );
        explain_buffer_software_error(sb);
        break;

    case EBADF:
        explain_buffer_ebadf(sb, fildes, "fildes");
        break;

    case ECONNREFUSED:
        explain_buffer_gettext
        (
            sb,


            i18n("the remote server is accessible but is not listening for "
            "connections to the given port; or, an intervening firewall "
            "refused the connection")
        );
        break;

    case EFAULT:
        explain_buffer_efault(sb, "sock_addr");
        break;

    case EINPROGRESS:
        explain_buffer_gettext
        (
            sb,


            i18n("the socket is non-blocking and the connection cannot "
            "be completed immediately")
        );
        explain_buffer_software_error(sb);
        break;

    case EINTR:
        explain_buffer_eintr(sb, "connect");
        break;

    case EISCONN:
        {
            struct sockaddr_storage sas;
            struct sockaddr *sa;
            socklen_t       siz;

            sa = (struct sockaddr *)&sas;
            siz = sizeof(sas);
            if (getsockname(fildes, sa, &siz) >= 0)
            {
                char            addr[500];
                explain_string_buffer_t addr_sb;

                explain_string_buffer_init(&addr_sb, addr, sizeof(addr));
                explain_buffer_sockaddr(&addr_sb, sa, siz);
                explain_string_buffer_printf_gettext
                (
                    sb,


                    i18n("the socket is already connected to %s"),
                    addr
                );
            }
            else
            {
                explain_buffer_gettext
                (
                    sb,


                    i18n("the socket is already connected to a network address")
                );
            }
            explain_buffer_software_error(sb);
        }
        break;

    case ENETUNREACH:

        explain_buffer_gettext
        (
            sb,


            i18n("network or host is unreachable; sometimes this is a "
            "routing issue, sometimes the network is physically "
            "disconnected, sometimes a router is turned off, sometimes "
            "the host is physically disconnected, sometimes the host is "
            "turned off")
        );
        break;

    case ENOTSOCK:
        explain_buffer_enotsock(sb, fildes, "fildes");
        break;

    case ETIMEDOUT:
        explain_buffer_gettext
        (
            sb,


            i18n("the connection attempt took to long; the server may be too "
            "busy to accept new connections, or an intervening firewall "
            "may be discarding your packets")
        );
        break;

    default:
        explain_buffer_errno_generic(sb, errnum, "connect");
        break;
    }
}
