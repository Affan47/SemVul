Ipv6ToIpv4SocketAccept (
    PRFileDesc *fd, PRNetAddr *addr, PRIntervalTime timeout)
{
    PRStatus rv;
    PRFileDesc *newfd;
    PRFileDesc *newstack;
	PRNetAddr tmp_ipv4addr;
    PRNetAddr *addrlower = NULL;

    PR_ASSERT(fd != NULL);
    PR_ASSERT(fd->lower != NULL);

    newstack = PR_NEW(PRFileDesc);
    if (NULL == newstack)
    {
        PR_SetError(PR_OUT_OF_MEMORY_ERROR, 0);
        return NULL;
    }
    *newstack = *fd;

    if (addr)
        addrlower = &tmp_ipv4addr;
    newfd = (fd->lower->methods->accept)(fd->lower, addrlower, timeout);
    if (NULL == newfd)
    {
        PR_DELETE(newstack);
        return NULL;
    }
    if (addr)
        _PR_ConvertToIpv6NetAddr(&tmp_ipv4addr, addr);

    rv = PR_PushIOLayer(newfd, PR_TOP_IO_LAYER, newstack);
    PR_ASSERT(PR_SUCCESS == rv);
    return newfd;
}
