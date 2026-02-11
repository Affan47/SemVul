RunServer(const char* pszApplication,
              const char* pszService,
              const char* pszUnixSocketFilename)
{
    int nListenSocket;

    if( pszUnixSocketFilename != NULL )
    {
        struct sockaddr_un sockAddrUnix;
        int len;

        nListenSocket = socket(AF_UNIX, SOCK_STREAM, 0);
        if (nListenSocket < 0)
        {
            perror("socket");
            return 1;
        }

        sockAddrUnix.sun_family = AF_UNIX;
        CPLStrlcpy(sockAddrUnix.sun_path, pszUnixSocketFilename, sizeof(sockAddrUnix.sun_path));
        unlink(sockAddrUnix.sun_path);
        len = strlen(sockAddrUnix.sun_path) + sizeof(sockAddrUnix.sun_family);
        if (bind(nListenSocket, (struct sockaddr *)&sockAddrUnix, len) == -1)
        {
            perror("bind");
            closesocket(nListenSocket);
            return 1;
        }
        if (listen(nListenSocket, SOMAXCONN) == SOCKET_ERROR)
        {
            fprintf(stderr, "listen() function failed with error: %d\n", WSAGetLastError());
            closesocket(nListenSocket);
            return 1;
        }
    }
    else
    {
        nListenSocket = CreateSocketAndBindAndListen(pszService, NULL, NULL, NULL);
        if (nListenSocket < 0)
        {
            return 1;
        }
    }

    while(TRUE)
    {
        struct sockaddr sockAddr;
        socklen_t nLen = sizeof(sockAddr);
        int nConnSocket;
        pid_t pid;
        int nStatus;
        struct timeval tv;
        fd_set read_fds;


        do
        {
            FD_ZERO(&read_fds);
            FD_SET(nListenSocket, &read_fds);
            tv.tv_sec = 1;
            tv.tv_usec = 0;
            waitpid(-1, &nStatus, WNOHANG);
        }
        while( select(nListenSocket + 1, &read_fds, NULL, NULL, &tv) != 1 );

        nConnSocket = accept(nListenSocket, &sockAddr, &nLen);
        if( nConnSocket < 0 )
        {
            fprintf(stderr, "accept() function failed with error: %d\n", errno);
            close(nListenSocket);
            return 1;
        }

        pid = fork();
        if( pid < 0 )
        {
            fprintf(stderr, "fork() failed: %d\n", errno);
            close(nListenSocket);
            close(nConnSocket);
            return 1;
        }
        else if( pid == 0 )
        {
            int nRet;
            close(nListenSocket);
            nRet = GDALServerLoopSocket(nConnSocket);
            close(nConnSocket);
            return nRet;
        }
        else
        {
            close(nConnSocket);
        }
    }
}
