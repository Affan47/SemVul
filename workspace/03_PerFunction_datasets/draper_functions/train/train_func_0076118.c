at2_start_cb(SMSCConn *conn)
{
    PrivAT2data *privdata;

    privdata = conn->data;
    if (conn->status == SMSCCONN_DISCONNECTED)
        conn->status = SMSCCONN_ACTIVE;


    gwthread_wakeup(privdata->device_thread);
    debug("smsc.at2", 0, "AT2[%s]: start called", octstr_get_cstr(privdata->name));
}
