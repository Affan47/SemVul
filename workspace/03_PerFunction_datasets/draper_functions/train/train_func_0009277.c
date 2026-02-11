smscconn_send(SMSCConn *conn, Msg *msg)
{
    int ret = -1;
    List *parts = NULL;

    gw_assert(conn != NULL);
    mutex_lock(conn->flow_mutex);
    if (conn->status == SMSCCONN_DEAD || conn->why_killed != SMSCCONN_ALIVE) {
        mutex_unlock(conn->flow_mutex);
        return -1;
    }


    if (msg->sms.split_parts == NULL) {

        char *uf = conn->unified_prefix ? octstr_get_cstr(conn->unified_prefix) : NULL;
        normalize_number(uf, &(msg->sms.receiver));


        parts = sms_split(msg, NULL, NULL, NULL, NULL, 1,
            counter_increase(split_msg_counter) & 0xff, 0xff, conn->max_sms_octets);
        if (gwlist_len(parts) == 1) {

            gwlist_destroy(parts, msg_destroy_item);
            parts = NULL;
        }
    }

    if (parts == NULL)
        ret = conn->send_msg(conn, msg);
    else {
        long i, parts_len = gwlist_len(parts);
        struct split_parts *split = gw_malloc(sizeof(*split));

        split->orig = msg_duplicate(msg);
        split->parts_left = counter_create();
        split->status = SMSCCONN_SUCCESS;
        counter_set(split->parts_left, parts_len);
        split->smsc_conn = conn;
        debug("bb.sms.splits", 0, "new split_parts created %p", split);
        for (i = 0; i < parts_len; i++) {
            msg = gwlist_get(parts, i);
            msg->sms.split_parts = split;
            ret = conn->send_msg(conn, msg);
            if (ret < 0) {
                if (i == 0) {
                    counter_destroy(split->parts_left);
                    gwlist_destroy(parts, msg_destroy_item);
                    gw_free(split);
                    mutex_unlock(conn->flow_mutex);
                    return ret;
                }


                split->status = SMSCCONN_FAILED_REJECTED;
                counter_increase_with(split->parts_left, -(parts_len - i));
                warning(0, "Could not send all parts of a split message");
                break;
            }
        }
        gwlist_destroy(parts, msg_destroy_item);
    }
    mutex_unlock(conn->flow_mutex);
    return ret;
}
