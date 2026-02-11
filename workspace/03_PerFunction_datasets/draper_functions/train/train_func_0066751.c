read_messages_from_bearerbox(void *arg)
{
    time_t start, t;
    unsigned long secs;
    unsigned long total_s, total_f, total_ft, total_b;
    Msg *msg;

    total_s = total_f = total_ft = total_b = 0;
    start = t = time(NULL);
    while (program_status != shutting_down) {
        int ret;

        ret = read_from_bearerbox(&msg, INFINITE_TIME);
        if (ret == -1)
            break;
        else if (ret == 1)
            continue;
        else if (msg == NULL)
            break;

        if (msg_type(msg) == admin) {
            if (msg->admin.command == cmd_shutdown ||
                msg->admin.command == cmd_restart) {
                info(0, "Bearerbox told us to die");
                program_status = shutting_down;
            }


            msg_destroy(msg);
        } else if (msg_type(msg) == ack) {
            switch (msg->ack.nack) {
                case ack_success:
                    total_s++;
                    break;
                case ack_failed:
                    total_f++;
                    break;
                case ack_failed_tmp:
                    total_ft++;
                    break;
                case ack_buffered:
                    total_b++;
                    break;
            }
            msg_destroy(msg);
        } else {
            warning(0, "Received other message than sms/admin, ignoring!");
            msg_destroy(msg);
        }
    }
    secs = difftime(time(NULL), start);
    info(0, "Received acks: %ld success, %ld failed, %ld failed temporarly, %ld queued in %ld seconds "
    	 "(%.2f per second)", total_s, total_f, total_ft, total_b, secs,
         (float)(total_s+total_f+total_ft+total_b) / secs);
}
