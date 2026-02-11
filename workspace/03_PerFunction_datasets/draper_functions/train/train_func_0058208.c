pt_connect_cont(pt_Continuation *op, PRInt16 revents)
{
    op->syserrno = _MD_unix_get_nonblocking_connect_error(op->arg1.osfd);
    if (op->syserrno != 0) {
        op->result.code = -1;
    } else {
        op->result.code = 0;
    }
    return PR_TRUE;
}
