chat_io_connect(
    chat_io_event_q_t                   q,
    char *                              hostname,
    int                                 port,
    chat_io_event_callback_t            cb,
    void *                              user_arg,
    int                                 mtimeout)
{
    struct hostent *                    hp;
    int                                 sock;
    struct sockaddr_in                  addr;
    int                                 done;
    int                                 rc;
    int                                 flags;
    chat_io_event_t *                   event;
    struct linger                       linger;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {
        goto error;
    }
    hp = gethostbyname(hostname);
    if(hp == NULL)
    {
        goto sock_close_error;
    }
    memset(&addr, '\0', sizeof(addr));
    addr.sin_family = hp->h_addrtype;
    memcpy(&addr.sin_addr,
           hp->h_addr,
           hp->h_length);
    addr.sin_port = htons(port);

    if(q->read_events[sock] != NULL)
    {
        goto error;
    }
    flags = fcntl(sock, F_GETFL);
    flags = flags | O_NONBLOCK;
    fcntl(sock, F_SETFL, flags);


    linger.l_onoff = 1;
    linger.l_linger = 100;
    if(setsockopt(sock, SOL_SOCKET, SO_LINGER, &linger,
        sizeof(linger)) < 0)
    {
        goto error;
    }

    do
    {
        done = TRUE;
        rc = connect(sock,(struct sockaddr *)&addr,
            sizeof(struct sockaddr_in));
        if(rc < 0)
        {
            switch(errno)
            {

                case EINTR:
                    done = FALSE;
                    break;

                case EINPROGRESS:
                    done = TRUE;
                    break;

                default:
                    goto sock_close_error;
            }
        }
    } while(!done);

    event = chat_l_create_event(q, sock, cb, user_arg, mtimeout);
    event->type = CHAT_IO_EVENT_TYPE_CONNECT;
    FD_SET(sock, &q->write_fd_set);
    q->write_events[sock] = event;

    return sock;

sock_close_error:
    close(sock);
error:
    return CHAT_ERROR_SOCKET;
}
