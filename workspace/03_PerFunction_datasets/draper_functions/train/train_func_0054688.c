rfbWriteExact(rfbClientPtr cl,
              const char *buf,
              int len)
{
    int sock = cl->sock;
    int n;
    fd_set fds;
    struct timeval tv;
    int totalTimeWaited = 0;
    const int timeout = (cl->screen && cl->screen->maxClientWait) ? cl->screen->maxClientWait : rfbMaxClientWait;

#undef DEBUG_WRITE_EXACT
#ifdef DEBUG_WRITE_EXACT
    rfbLog("WriteExact %d bytes\n",len);
    for(n=0;n<len;n++)
	    fprintf(stderr,"%02x ",(unsigned char)buf[n]);
    fprintf(stderr,"\n");
#endif

    LOCK(cl->outputMutex);
    while (len > 0) {
        n = write(sock, buf, len);

        if (n > 0) {

            buf += n;
            len -= n;

        } else if (n == 0) {

            rfbErr("WriteExact: write returned 0?\n");
            return 0;

        } else {
#ifdef WIN32
			errno = WSAGetLastError();
#endif
	    if (errno == EINTR)
		continue;

            if (errno != EWOULDBLOCK && errno != EAGAIN) {
	        UNLOCK(cl->outputMutex);
                return n;
            }


            FD_ZERO(&fds);
            FD_SET(sock, &fds);
            tv.tv_sec = 5;
            tv.tv_usec = 0;
            n = select(sock+1, NULL, &fds, NULL , &tv);
	    if (n < 0) {
#ifdef WIN32
                errno=WSAGetLastError();
#endif
       	        if(errno==EINTR)
		    continue;
                rfbLogPerror("WriteExact: select");
                UNLOCK(cl->outputMutex);
                return n;
            }
            if (n == 0) {
                totalTimeWaited += 5000;
                if (totalTimeWaited >= timeout) {
                    errno = ETIMEDOUT;
                    UNLOCK(cl->outputMutex);
                    return -1;
                }
            } else {
                totalTimeWaited = 0;
            }
        }
    }
    UNLOCK(cl->outputMutex);
    return 1;
}
