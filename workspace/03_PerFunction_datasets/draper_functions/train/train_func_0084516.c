channelEvent(unsigned char *ant_message) {

    unsigned char *message=ant_message+2;


    if (MESSAGE_IS_RESPONSE_NO_ERROR(message)) {

        attemptTransition(RESPONSE_NO_ERROR_MESSAGE_ID(message));

    } else if (MESSAGE_IS_EVENT_CHANNEL_CLOSED(message)) {

        parent->sendMessage(ANTMessage::unassignChannel(number));

    } else if (MESSAGE_IS_EVENT_RX_SEARCH_TIMEOUT(message)) {


        if (channel_type_flags & CHANNEL_TYPE_QUICK_SEARCH) {

            channel_type_flags &= ~CHANNEL_TYPE_QUICK_SEARCH;
            channel_type_flags |= CHANNEL_TYPE_WAITING;

            emit searchTimeout(number);

        } else {

            emit lostInfo(number);


            parent->sendMessage(ANTMessage::unassignChannel(number));
        }

    } else if (MESSAGE_IS_EVENT_RX_FAIL(message)) {

        messages_dropped++;
        double t=get_timestamp();

        if (t > (last_message_timestamp + timeout_drop)) {
            if (channel_type != CHANNEL_TYPE_UNUSED) emit dropInfo(number, messages_dropped, messages_received);

            last_message_timestamp+=2*timeout_drop;
        }

    } else if (MESSAGE_IS_EVENT_RX_ACKNOWLEDGED(message)) {

        exit(-10);

    } else if (MESSAGE_IS_EVENT_TRANSFER_TX_COMPLETED(message)) {

    }
}
