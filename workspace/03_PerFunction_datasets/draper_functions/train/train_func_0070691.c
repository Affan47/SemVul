setupNetwork(int fd)
{
    socklen_t addrlen;

    addrlen = sizeof (peer_addr);
    if (Socket::getpeername(fd, &peer_addr, &addrlen) < 0) {
        logError("getpeername: %m (incorrect hfaxd invocation?)");
        dologout(-1);
    }
    addrlen = sizeof (ctrl_addr);
    if (Socket::getsockname(fd, &ctrl_addr, &addrlen) < 0) {
        logError("getsockname: %m");
        dologout(-1);
    }
#if defined(IPTOS_LOWDELAY)
    { int tos = IPTOS_LOWDELAY;
      if (Socket::setsockopt(fd, IPPROTO_IP, IP_TOS, &tos, sizeof (tos)) < 0)
          logWarning("setsockopt (IP_TOS): %m");
    }
#endif
#if defined(SO_LINGER) && !defined(__linux__)
    { struct linger opt;
      opt.l_onoff = 1;
      opt.l_linger = 60;
      if (Socket::setsockopt(fd, SOL_SOCKET, SO_LINGER, &opt, sizeof (opt)) < 0)
	logWarning("setsockopt (SO_LINGER): %m");
    }
#endif

    data_source = ctrl_addr;
    Socket::port(data_source) = htons(ntohs(Socket::port(ctrl_addr))-1);
#ifdef  F_SETOWN
    if (fcntl(fd, F_SETOWN, getpid()) == -1)
        logError("fcntl (F_SETOWN): %m");
#endif
#if defined(SO_OOBINLINE)

    { int on = 1;
      if (Socket::setsockopt(fd, SOL_SOCKET, SO_OOBINLINE, &on, sizeof (on)) < 0)
        logError("setsockopt (SO_OOBINLINE): %m");
    }
#endif
#ifdef SIGURG


    signal(SIGURG, fxSIGHANDLER(sigURG));
#endif
    signal(SIGPIPE, fxSIGHANDLER(sigPIPE));

    char hostbuf[128];

    remoteaddr = inet_ntop(Socket::family(peer_addr), Socket::addr(peer_addr), hostbuf, sizeof(hostbuf));

    getnameinfo((struct sockaddr*)&peer_addr, Socket::socklen(peer_addr),
		    hostbuf, sizeof(hostbuf), NULL, 0, 0);

    if (remoteaddr == "0.0.0.0")
        remotehost = "localhost";
    else if (checkHostIdentity(hostbuf))
	remotehost = hostbuf;
    else
	remotehost =  remoteaddr;
    Dispatcher::instance().link(STDIN_FILENO, Dispatcher::ReadMask, this);
}
