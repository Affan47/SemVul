finreq(int a2fd, int status, int result)
{
    char finbuf[2];
    struct a2request *a2req = a2reqlist;
    if (a2req->next)
    {


        finbuf[0] = a2req->next->type;
        write(a2fd, finbuf, 1);
    }


    if (a2client[a2req->idx].flags & CLIENT_OPEN)
    {
        if (a2req->type == 0x90)
            write(a2client[a2req->idx].fd, a2req->buffer, a2req->count);
        finbuf[0] = status;
        finbuf[1] = result;
        write(a2client[a2req->idx].fd, finbuf, 2);
    }
    if (a2req->buffer)
    {
        free(a2req->buffer);
        a2req->buffer = NULL;
    }


    a2reqlist   = a2req->next;
    a2req->next = a2reqfree;
    a2reqfree   = a2req;
}
