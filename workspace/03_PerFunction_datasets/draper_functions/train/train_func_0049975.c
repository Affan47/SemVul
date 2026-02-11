read_messages_from_bearerbox(void)
{
    time_t start, t;
    int secs;
    int total = 0;
    int ret;
    Msg *msg;

    start = t = time(NULL);
    while (program_status != shutting_down) {

        ret = read_from_bearerbox(&msg, INFINITE_TIME);
        if (ret == -1) {
            error(0, "Bearerbox is gone, restarting");
            program_status = shutting_down;
            restart = 1;
            break;
        } else if (ret == 1)
            continue;
        else if (msg == NULL)
            break;

	if (msg_type(msg) == admin) {
	    if (msg->admin.command == cmd_shutdown) {
		info(0, "Bearerbox told us to die");
		program_status = shutting_down;
	    } else if (msg->admin.command == cmd_restart) {
		info(0, "Bearerbox told us to restart");
		restart = 1;
		program_status = shutting_down;
	    }


	    msg_destroy(msg);
	} else if (msg_type(msg) == sms) {
	    if (total == 0)
		start = time(NULL);
	    total++;
	    gwlist_produce(smsbox_requests, msg);
	} else if (msg_type(msg) == ack) {
	    if (!immediate_sendsms_reply)
		delayed_http_reply(msg);
	    msg_destroy(msg);
	} else {
	    warning(0, "Received other message than sms/admin, ignoring!");
	    msg_destroy(msg);
	}
    }
    secs = difftime(time(NULL), start);
    info(0, "Received (and handled?) %d requests in %d seconds "
    	 "(%.2f per second)", total, secs, (float)total / secs);
}
