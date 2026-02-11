AcceptConnection(
    QString& sClientIPOut)
{
    sockaddr_in clientAddr;
    #ifdef WIN32
    int nAddrSize = sizeof(clientAddr);
    #else
    unsigned int nAddrSize = sizeof(clientAddr);
    #endif

    Q_ASSERT(mListeningSocket != INVALID_SOCKET);


    mTalkSocket = accept(mListeningSocket,
                         reinterpret_cast<sockaddr*>(&clientAddr),
                         &nAddrSize);


    if (mTalkSocket == INVALID_SOCKET)
    {


        int nErrorCode = LastError();
        QString err = tr("Accept socket connection failed. Socket error: %1").arg( nErrorCode );
        if (nErrorCode == WSAENETDOWN ||
            nErrorCode == WSAEMFILE ||
            nErrorCode == WSAENOBUFS ||
            nErrorCode == WSAEFAULT)
        {

            CloseSocket(mListeningSocket);
            throw NetworkException((err));
        }
        else
        {

            Q_ASSERT(false);
            CloseSocket(mListeningSocket);
            throw NetworkException((err));
        }
    }


    #ifndef WIN32
    struct timeval nTimeout;
    nTimeout.tv_sec = 0;
    nTimeout.tv_usec = RECV_TIMEOUT;
    #endif

    #ifdef WIN32
    int nTimeout = RECV_TIMEOUT;
    #endif


    int nResult = setsockopt(
        mTalkSocket,
        SOL_SOCKET,
        SO_RCVTIMEO,
    #ifdef WIN32
        (const char*)&nTimeout,
    #endif
    #ifndef WIN32
        &nTimeout,
    #endif
        sizeof( nTimeout ) );

    if (nResult == SOCKET_ERROR)
    {
        int nErrorCode = LastError();
        LOG(1, "Set socket timeout failed. Socket error: " << nErrorCode << "\n");
        Q_ASSERT(false);
    }


    char* pcClientIP = inet_ntoa(clientAddr.sin_addr);
    sClientIPOut = pcClientIP;
}
