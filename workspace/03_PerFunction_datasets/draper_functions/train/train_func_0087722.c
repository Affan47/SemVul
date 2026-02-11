httpsmsc_queued(SMSCConn *conn)
{
    ConnData *conndata = conn->data;

    return (conndata ? (conn->status != SMSCCONN_DEAD ?
            conndata->open_sends : 0) : 0);
}
