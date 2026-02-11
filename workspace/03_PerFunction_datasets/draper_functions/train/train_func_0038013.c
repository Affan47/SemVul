start_cb(SMSCConn *conn)
{
    PrivData *privdata = conn->data;


    if (privdata->rport > 0)
	gwthread_wakeup(privdata->receiver_thread);
    debug("smsc.emi2", 0, "EMI2[%s]: start called",
	  octstr_get_cstr(privdata->name));
}
