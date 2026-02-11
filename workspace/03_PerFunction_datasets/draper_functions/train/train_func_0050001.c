pkix_pl_Socket_Send(
        PKIX_PL_Socket *sendSock,
        void *buf,
        PKIX_UInt32 bytesToWrite,
        PKIX_Int32 *pBytesWritten,
        void *plContext)
{
        PRInt32 bytesWritten = 0;
        PRErrorCode errorcode = 0;
        PRFileDesc *fd = NULL;

        PKIX_ENTER(SOCKET, "pkix_pl_Socket_Send");
        PKIX_NULLCHECK_TWO(buf, pBytesWritten);

        fd = sendSock->clientSock;

        PKIX_PL_NSSCALLRV(SOCKET, bytesWritten, PR_Send,
                (fd, buf, (PRInt32)bytesToWrite, 0, sendSock->timeout));

        if (bytesWritten >= 0) {
                if (sendSock->status == SOCKET_SENDRCVPENDING) {
                        sendSock->status = SOCKET_RCVPENDING;
                } else {
                        sendSock->status = SOCKET_CONNECTED;
                }
#ifdef PKIX_SOCKETTRACE
                pkix_pl_socket_tracebuff(buf, bytesWritten);
#endif
        } else {
                errorcode = PR_GetError();
                if (errorcode != PR_WOULD_BLOCK_ERROR) {
#ifdef PKIX_SOCKETDEBUG
                        printf
                                ("pkix_pl_Socket_Send: %s\n",
                                PR_ErrorToString(errorcode, PR_LANGUAGE_EN));
#endif
                        PKIX_ERROR(PKIX_PRSENDFAILED);
                }

                sendSock->writeBuf = buf;
                sendSock->writeBufSize = bytesToWrite;
                if (sendSock->status == SOCKET_RCVPENDING) {
                        sendSock->status = SOCKET_SENDRCVPENDING;
                } else {
                        sendSock->status = SOCKET_SENDPENDING;
                }
        }

        *pBytesWritten = (PKIX_Int32)bytesWritten;

cleanup:

        PKIX_RETURN(SOCKET);
}
