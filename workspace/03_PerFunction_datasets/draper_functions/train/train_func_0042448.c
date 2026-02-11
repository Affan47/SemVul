smsbox_to_bearerbox(void *arg)
{
    Boxc *conn = arg;
    Msg *msg;


    while (sqlbox_status != SQL_DEAD && conn->alive) {


        msg = read_from_box(conn->smsbox_connection, conn);

        if (msg == NULL) {
            conn->alive = 0;
            break;
        }

        if (msg_type(msg) == sms) {
            debug("sqlbox", 0, "smsbox_to_bearerbox: sms received");

            gw_sql_save_msg(msg, octstr_imm("MT"));
        }

        send_msg(conn->bearerbox_connection, conn, msg);

        if (msg_type(msg) == admin && msg->admin.command == cmd_identify) {


            if (msg->admin.boxc_id != NULL) {


                conn->boxc_id = msg->admin.boxc_id;
                msg->admin.boxc_id = NULL;

                debug("sqlbox", 0, "smsbox_to_bearerbox: got boxc_id <%s> from <%s>",
                      octstr_get_cstr(conn->boxc_id),
                      octstr_get_cstr(conn->client_ip));
            }
        }
        msg_destroy(msg);
    }
    conn->alive = 0;
}
