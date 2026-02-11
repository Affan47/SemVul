ois_adjust_originating_address(Msg *msg, const char *raw)
{
    int len;

    SAY(3, "ois_adjust_originating_address");

    len = raw[0] & 0xff;
    msg->sms.sender = octstr_create_from_data(&raw[1+2], len-2);

    return 1 + len;
}
