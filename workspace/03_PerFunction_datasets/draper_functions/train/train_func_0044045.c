ois_adjust_additional_information(Msg *msg, const char *raw)
{
    SAY(3, "ois_adjust_additional_information");


    msg->sms.mclass = raw[0] & 0xff;

    return 1;
}
