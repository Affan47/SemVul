pt_RecvFrom(PRFileDesc *fd, void *buf, PRInt32 amount,
    PRIntn flags, PRNetAddr *addr, PRIntervalTime timeout)
{
    PRBool fNeedContinue = PR_FALSE;
    PRInt32 syserrno, bytes = -1;
    pt_SockLen addr_len = sizeof(PRNetAddr);

    if (pt_TestAbort()) return bytes;

    bytes = recvfrom(
        fd->secret->md.osfd, buf, amount, flags,
        (struct sockaddr*)addr, &addr_len);
    syserrno = errno;

    if ( (bytes == -1) && (syserrno == EWOULDBLOCK || syserrno == EAGAIN)
        && (!fd->secret->nonblocking) )
    {
        if (PR_INTERVAL_NO_WAIT == timeout) syserrno = ETIMEDOUT;
        else fNeedContinue = PR_TRUE;
    }

    if (fNeedContinue == PR_TRUE)
    {
        pt_Continuation op;
        op.arg1.osfd = fd->secret->md.osfd;
        op.arg2.buffer = buf;
        op.arg3.amount = amount;
        op.arg4.flags = flags;
        op.arg5.addr = addr;
        op.timeout = timeout;
        op.function = pt_recvfrom_cont;
        op.event = POLLIN | POLLPRI;
        bytes = pt_Continue(&op);
        syserrno = op.syserrno;
    }
    if (bytes >= 0)
    {
#ifdef _PR_HAVE_SOCKADDR_LEN

        if (addr)
        {
            addr->raw.family = ((struct sockaddr*)addr)->sa_family;
        }
#endif
#ifdef _PR_INET6
        if (addr && (AF_INET6 == addr->raw.family))
            addr->raw.family = PR_AF_INET6;
#endif
    }
    else
        pt_MapError(_PR_MD_MAP_RECVFROM_ERROR, syserrno);
    return bytes;
}
