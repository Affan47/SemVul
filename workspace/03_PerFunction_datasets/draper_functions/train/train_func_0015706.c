send_alive(struct sockaddr *from, int fromlen, int length, int fd)
{
    CARD32 sessionID;
    CARD16 displayNumber;
    struct display *d;
    XdmcpHeader header;
    CARD8 sendRunning;
    CARD32 sendSessionID;

    debug("send <alive>\n");
    if (XdmcpReadCARD16(&buffer, &displayNumber) &&
        XdmcpReadCARD32(&buffer, &sessionID))
    {
        if (length == 6) {
            if (!(d = findDisplayBySessionID(sessionID)))
                d = findDisplayByAddress((XdmcpNetaddr)from, fromlen,
                                         displayNumber);
            sendRunning = 0;
            sendSessionID = 0;
            if (d && d->status == running) {
                if (d->sessionID == sessionID)
                    sendRunning = 1;
                sendSessionID = d->sessionID;
            }
            header.version = XDM_PROTOCOL_VERSION;
            header.opcode = (CARD16)ALIVE;
            header.length = 5;
            debug("<alive>: %d %ld\n", sendRunning, (long)sendSessionID);
            XdmcpWriteHeader(&buffer, &header);
            XdmcpWriteCARD8(&buffer, sendRunning);
            XdmcpWriteCARD32(&buffer, sendSessionID);
            XdmcpFlush(fd, &buffer, (XdmcpNetaddr)from, fromlen);
        }
    }
}
