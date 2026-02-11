smasi_thread(void *arg)
{
    long pending_submits;
    long len;
    SMASI_PDU *pdu;
    SMASI *smasi;
    int logoff_already_sent = 0;
    int ret;
    Connection *conn;
    long last_enquire_sent;
    double timeout;

    smasi = arg;


    log_thread_to(smasi->conn->log_idx);

    while (!smasi->quitting) {

        conn = open_connection(smasi);
        if (conn == NULL) {
            error(0, "SMASI[%s]: Could not connect to SMSC center " \
                  "(retrying in %ld seconds).",
                  octstr_get_cstr(smasi->conn->id), smasi->conn->reconnect_delay);

            gwthread_sleep(smasi->conn->reconnect_delay);
            smasi->conn->status = SMSCCONN_RECONNECTING;
            continue;
        }

        last_enquire_sent = date_universal_now();
        pending_submits = -1;
        len = 0;

        for (;;) {
            timeout = last_enquire_sent + smasi->enquire_link_interval
                        - date_universal_now();


            if (conn_wait(conn, timeout) == -1) {
                error(0, "SMASI[%s]: I/O error or other error. Re-connecting.",
                      octstr_get_cstr(smasi->conn->id));
                break;
            }


            if (smasi->quitting && !logoff_already_sent) {
                send_logoff(smasi, conn);
                logoff_already_sent = 1;
            }


            send_enquire_link(smasi, conn, &last_enquire_sent);


            while ((ret = read_pdu(smasi, conn, &pdu)) == 1) {

                dump_pdu("Got PDU:", smasi->conn->id, pdu);


                handle_pdu(smasi, conn, pdu, &pending_submits);

                smasi_pdu_destroy(pdu);


                if (smasi->logged_off) break;


                if ((!smasi->throttling_err_time ||
                    ((time(NULL) - smasi->throttling_err_time) >
                     SMASI_THROTTLING_SLEEP_TIME
                      && !(smasi->throttling_err_time = 0))))
                    send_messages(smasi, conn, &pending_submits);
            }


            if (ret == -1) {
                error(0, "SMASI[%s]: I/O error or other error. Re-connecting.",
                      octstr_get_cstr(smasi->conn->id));
                break;
            }


            if (smasi->logged_off) break;

            if ((!smasi->throttling_err_time ||
                ((time(NULL) - smasi->throttling_err_time) >
                 SMASI_THROTTLING_SLEEP_TIME
                  && !(smasi->throttling_err_time = 0))))
                send_messages(smasi, conn, &pending_submits);

        }

        conn_destroy(conn);
        conn = NULL;
    }
}
