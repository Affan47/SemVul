main_connection_loop(SMSCConn *conn, Connection *client)
{
    PrivData *privdata = conn->data;
    Octstr *line;
    Msg	*msg;
    double delay = 0;

    if (conn->throughput > 0) {
        delay = 1.0 / conn->throughput;
    }

    while (1) {
        while (!conn->is_stopped && !privdata->shutdown &&
                (line = conn_read_line(client)))
            msg_to_bb(conn, line);
        if (conn_error(client))
            goto error;
        if (conn_eof(client))
            goto eof;


        while ((msg = gwlist_extract_first(privdata->outgoing_queue)) != NULL) {


            if (sms_to_client(client, msg) == 1) {
                Msg *copy = msg_duplicate(msg);


                bb_smscconn_sent(conn, msg, NULL);


                if (DLR_IS_SUCCESS_OR_FAIL(copy->sms.dlr_mask)) {
                    Msg *dlrmsg;
                    Octstr *tmp;
                    int dlrstat = DLR_SUCCESS;
                    char id[UUID_STR_LEN + 1];

                    uuid_unparse(copy->sms.id, id);
                    tmp = octstr_create(id);
                    dlrmsg = dlr_find(conn->id,
                                      tmp,
                                      copy->sms.receiver,
                                      dlrstat, 0);
                    if (dlrmsg != NULL) {

                        bb_smscconn_receive(conn, dlrmsg);
                    } else {
                        error(0,"smsc_fale: got DLR but could not find message or was not interested in it");
                    }
                    octstr_destroy(tmp);
                }
                msg_destroy(copy);

            } else {
                bb_smscconn_send_failed(conn, msg,
		            SMSCCONN_FAILED_REJECTED, octstr_create("REJECTED"));
                goto error;
            }


            if (conn->throughput > 0) {
                gwthread_sleep(delay);
            }
        }
        if (privdata->shutdown) {
            debug("bb.sms", 0, "smsc_fake shutting down, closing client socket");
            conn_destroy(client);
            return;
        }
        conn_wait(client, -1);
        if (conn_error(client))
            goto error;
        if (conn_eof(client))
            goto eof;
    }
error:
    info(0, "IO error to fakesmsc client. Closing connection.");
    conn_destroy(client);
    return;
eof:
    info(0, "EOF from fakesmsc client. Closing connection.");
    conn_destroy(client);
    return;
}
