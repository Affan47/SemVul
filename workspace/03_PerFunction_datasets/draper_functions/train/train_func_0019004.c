cgw_send_loop(SMSCConn *conn, Connection *server)
{
    PrivData *privdata = conn->data;
    struct cgwop *cgwop;
    Msg	*msg;
    int firsttrn;


    while ((msg = gwlist_extract_first(privdata->outgoing_queue)) != NULL) {
        firsttrn = privdata->nexttrn;
        while (privdata->sendtime[privdata->nexttrn] != 0) {
            if (++privdata->nexttrn >= CGW_TRN_MAX) privdata->nexttrn = 0;
            if (privdata->nexttrn == firsttrn) {


                info(0, "cgw: Saturated, increase size of CGW_TRN_MAX!");
                gwlist_produce(privdata->outgoing_queue, msg);
                return 1;
            }
        }

        cgwop = msg_to_cgwop(privdata, msg, privdata->nexttrn);

        if (cgwop == NULL) {
            info(0, "cgw: cgwop == NULL");
            return 0;
        }

        privdata->sendmsg[privdata->nexttrn] = msg;
        privdata->sendtime[privdata->nexttrn] = time(NULL);

        if (cgwop_send(server, cgwop) == -1) {
            cgwop_destroy(cgwop);
            info(0, "cgw: Unable to send (cgwop_send() == -1)");
            return -1;
        }

        privdata->unacked++;

        cgwop_destroy(cgwop);
    }
    return 0;
}
