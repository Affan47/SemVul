soap_queued_cb(SMSCConn *conn)
{
    PrivData *privdata = conn->data;
    long ret;


    if (conn->status == SMSCCONN_DEAD)
        return -1;

    ret = gwlist_len(privdata->outgoing_queue);


    conn->load = ret;

    return ret;
}
