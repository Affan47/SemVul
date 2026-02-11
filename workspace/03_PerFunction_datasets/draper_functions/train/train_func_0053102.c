channelId(unsigned char *ant_message) {

    unsigned char *message=ant_message+2;

    device_number=CHANNEL_ID_DEVICE_NUMBER(message);
    device_id=CHANNEL_ID_DEVICE_TYPE_ID(message);
    state=MESSAGE_RECEIVED;
    emit channelInfo(number, device_number, device_id);
    setId();


    if (channel_type_flags & CHANNEL_TYPE_QUICK_SEARCH) {
        parent->sendMessage(ANTMessage::setSearchTimeout(number, (int)(timeout_lost/2.5)));
    }
    channel_type_flags &= ~CHANNEL_TYPE_QUICK_SEARCH;
}
