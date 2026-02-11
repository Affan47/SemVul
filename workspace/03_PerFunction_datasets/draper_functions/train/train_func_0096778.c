handle_split(SMSCConn *conn, Msg *msg, long reason)
{
    struct split_parts *split = msg->sms.split_parts;


    if (reason == SMSCCONN_FAILED_TEMPORARILY && smscconn_status(conn) == SMSCCONN_ACTIVE &&
        smscconn_send(conn, msg) == 0) {

        msg_destroy(msg);
        return;
    }


    switch(reason) {
    case SMSCCONN_FAILED_DISCARDED:
    case SMSCCONN_FAILED_REJECTED:
    case SMSCCONN_FAILED_MALFORMED:
        debug("bb.sms.splits", 0, "Set split msg status to %ld", reason);
        split->status = reason;
        break;
    case SMSCCONN_SUCCESS:
        break;
    default:
        if (split->status == SMSCCONN_SUCCESS) {
            debug("bb.sms.splits", 0, "Set split msg status to %ld", reason);
            split->status = reason;
        }
        break;
    }


    msg_destroy(msg);

    if (counter_decrease(split->parts_left) <= 1) {

        counter_destroy(split->parts_left);
        msg = split->orig;
        msg->sms.split_parts = NULL;
        if (split->status == SMSCCONN_SUCCESS)
            bb_smscconn_sent(conn, msg, NULL);
        else {
            debug("bb.sms.splits", 0, "Parts of concatenated message failed.");
            bb_smscconn_send_failed(conn, msg, split->status, NULL);
        }
        gw_free(split);
    }
}
