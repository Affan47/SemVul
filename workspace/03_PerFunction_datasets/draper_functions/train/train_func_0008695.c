store_file_save_ack(Msg *msg, ack_status_t status)
{
    Msg *mack;
    int ret;


    if (!msg || msg_type(msg) != sms)
        return -1;

    if (filename == NULL)
        return 0;

    mack = msg_create(ack);
    if (!mack)
        return -1;

    mack->ack.time = msg->sms.time;
    uuid_copy(mack->ack.id, msg->sms.id);
    mack->ack.nack = status;

    ret = store_save(mack);
    msg_destroy(mack);

    return ret;
}
