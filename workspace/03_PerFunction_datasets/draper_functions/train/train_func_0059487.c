pkix_pl_Socket_CreateByName(
        PKIX_Boolean isServer,
        PRIntervalTime timeout,
        char *serverName,
        PRErrorCode *pStatus,
        PKIX_PL_Socket **pSocket,
        void *plContext)
{
        PRNetAddr netAddr;
        PKIX_PL_Socket *socket = NULL;
        char *sepPtr = NULL;
        PRHostEnt hostent;
        PRIntn hostenum;
        PRStatus prstatus = PR_FAILURE;
        char buf[PR_NETDB_BUF_SIZE];
        PRUint16 portNum = 0;
        char *localCopyName = NULL;

        PKIX_ENTER(SOCKET, "pkix_pl_Socket_CreateByName");
        PKIX_NULLCHECK_TWO(serverName, pSocket);

        localCopyName = PL_strdup(serverName);

        sepPtr = strchr(localCopyName, ':');

        if (sepPtr) {
                *sepPtr++ = '\0';
                 portNum = (PRUint16)atoi(sepPtr);
        } else {
                 portNum = (PRUint16)LDAP_PORT;
        }

        prstatus = PR_GetHostByName(localCopyName, buf, sizeof(buf), &hostent);

        if ((prstatus != PR_SUCCESS) || (hostent.h_length != 4)) {


                sepPtr = strchr(localCopyName, '.');
                if (sepPtr) {
                        *sepPtr++ = '\0';
                }
                prstatus = PR_GetHostByName
                        (localCopyName, buf, sizeof(buf), &hostent);

                if ((prstatus != PR_SUCCESS) || (hostent.h_length != 4)) {
                        PKIX_ERROR
                                (PKIX_PRGETHOSTBYNAMEREJECTSHOSTNAMEARGUMENT);
                }
        }

        netAddr.inet.family = PR_AF_INET;
        netAddr.inet.port = PR_htons(portNum);

        if (isServer) {

                netAddr.inet.ip = PR_INADDR_ANY;

        } else {

                hostenum = PR_EnumerateHostEnt(0, &hostent, portNum, &netAddr);
                if (hostenum == -1) {
                        PKIX_ERROR(PKIX_PRENUMERATEHOSTENTFAILED);
                }
        }

        PKIX_CHECK(PKIX_PL_Object_Alloc
                (PKIX_SOCKET_TYPE,
                sizeof (PKIX_PL_Socket),
                (PKIX_PL_Object **)&socket,
                plContext),
                PKIX_COULDNOTCREATESOCKETOBJECT);

        socket->isServer = isServer;
        socket->timeout = timeout;
        socket->clientSock = NULL;
        socket->serverSock = NULL;
        socket->netAddr = &netAddr;

        socket->callbackList.listenCallback = pkix_pl_Socket_Listen;
        socket->callbackList.acceptCallback = pkix_pl_Socket_Accept;
        socket->callbackList.connectcontinueCallback =
                 pkix_pl_Socket_ConnectContinue;
        socket->callbackList.sendCallback = pkix_pl_Socket_Send;
        socket->callbackList.recvCallback = pkix_pl_Socket_Recv;
        socket->callbackList.pollCallback = pkix_pl_Socket_Poll;
        socket->callbackList.shutdownCallback = pkix_pl_Socket_Shutdown;

        if (isServer) {
                PKIX_CHECK(pkix_pl_Socket_CreateServer(socket, plContext),
                        PKIX_SOCKETCREATESERVERFAILED);
                *pStatus = 0;
        } else {
                PKIX_CHECK(pkix_pl_Socket_CreateClient(socket, plContext),
                        PKIX_SOCKETCREATECLIENTFAILED);
                PKIX_CHECK(pkix_pl_Socket_Connect(socket, pStatus, plContext),
                        PKIX_SOCKETCONNECTFAILED);
        }

        *pSocket = socket;

cleanup:
        PL_strfree(localCopyName);

        if (PKIX_ERROR_RECEIVED) {
                PKIX_DECREF(socket);
        }

        PKIX_RETURN(SOCKET);
}
