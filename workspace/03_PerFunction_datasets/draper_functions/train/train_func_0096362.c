pt_sendto_cont(pt_Continuation *op, PRInt16 revents)
{
    PRIntn bytes = sendto(
        op->arg1.osfd, op->arg2.buffer, op->arg3.amount, op->arg4.flags,
        (struct sockaddr*)op->arg5.addr, PR_NETADDR_SIZE(op->arg5.addr));
    op->syserrno = errno;
    if (bytes >= 0)
    {
        char *bp = (char*)op->arg2.buffer;
        bp += bytes;
        op->arg2.buffer = bp;
        op->result.code += bytes;
        op->arg3.amount -= bytes;
        return (0 == op->arg3.amount) ? PR_TRUE : PR_FALSE;
    }
    else if ((EWOULDBLOCK != op->syserrno) && (EAGAIN != op->syserrno))
    {
        op->result.code = -1;
        return PR_TRUE;
    }
    else return PR_FALSE;
}
