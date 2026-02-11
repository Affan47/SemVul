at2_read_sms_memory(PrivAT2data* privdata)
{

    if (at2_check_sms_memory(privdata) == -1) {
        debug("bb.smsc.at2", 0, "AT2[%s]: memory check error", octstr_get_cstr(privdata->name));
        return -1;
    }

    if (privdata->sms_memory_usage) {


        int i;
        int message_count = 0;

        debug("bb.smsc.at2", 0, "AT2[%s]: %d messages waiting in memory",
              octstr_get_cstr(privdata->name), privdata->sms_memory_usage);


        for (i = 1; i <= privdata->sms_memory_capacity &&
             message_count < privdata->sms_memory_usage; ++i) {


            while (gwlist_len(privdata->pending_incoming_messages) > 0) {
                at2_read_pending_incoming_messages(privdata);
            }

            message_count += at2_read_delete_message(privdata, i);
        }
    }


    return 0;
}
