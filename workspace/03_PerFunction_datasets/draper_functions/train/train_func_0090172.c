io_thread (void *arg)
{
    Msg       *msg;
    SMSCConn  *conn = arg;
    PrivData *pdata = conn->data;
    double    sleep = 0.0001;


    log_thread_to(conn->log_idx);


    while (!pdata->quitting) {

        gwlist_consume(pdata->stopped);


        if (conn->status != SMSCCONN_ACTIVE) {
            if (cimd2_login(conn) != 0) {
                error(0, "CIMD2[%s]: Couldn't connect to SMSC (retrying in %ld seconds).",
                      octstr_get_cstr(conn->id),
                      conn->reconnect_delay);
                gwthread_sleep(conn->reconnect_delay);
                mutex_lock(conn->flow_mutex);
                conn->status = SMSCCONN_RECONNECTING;
                mutex_unlock(conn->flow_mutex);
                continue;
            }
            mutex_lock(conn->flow_mutex);
            conn->status = SMSCCONN_ACTIVE;
            conn->connect_time = time(NULL);
            bb_smscconn_connected(conn);
            mutex_unlock(conn->flow_mutex);
        }


        do {
            msg = sms_receive(conn);
            if (msg) {
                sleep = 0;
                debug("bb.sms.cimd2", 0, "CIMD2[%s]: new message received",
                      octstr_get_cstr(conn->id));
                bb_smscconn_receive(conn, msg);
            }
        } while (msg);


        do {
            msg = gwlist_extract_first(pdata->outgoing_queue);
            if (msg) {
                sleep = 0;
                if (cimd2_submit_msg(conn,msg) != 0) break;
            }
        } while (msg);

        if (sleep > 0) {


            gwthread_sleep(sleep);


            sleep *= 2;
            if (sleep >= 2.0)
                sleep = 1.999999;
        }
        else {
            sleep = 0.0001;
        }
    }
}
