attemptTransition(int message_id)
{

    const ant_sensor_type_t *st;
    int previous_state=state;
    st=&(parent->ant_sensor_types[channel_type]);


    state=message_id;


    switch (state) {

    case ANT_CLOSE_CHANNEL:


        state=MESSAGE_RECEIVED;
        break;

    case ANT_UNASSIGN_CHANNEL:
        channel_assigned=0;


        parent->sendMessage(ANTMessage::unassignChannel(number));


        parent->sendMessage(ANTMessage::assignChannel(number, 0, st->network));
        device_id=st->device_id;
        parent->sendMessage(ANTMessage::setChannelID(number, 0, device_id, 0));
        setId();
        break;

    case ANT_ASSIGN_CHANNEL:
        channel_assigned=1;
        parent->sendMessage(ANTMessage::setChannelID(number, device_number, device_id, 0));
        break;

    case ANT_CHANNEL_ID:
        if (channel_type & CHANNEL_TYPE_QUICK_SEARCH) {
            parent->sendMessage(ANTMessage::setSearchTimeout(number, (int)(timeout_scan/2.5)));
        } else {
            parent->sendMessage(ANTMessage::setSearchTimeout(number, (int)(timeout_lost/2.5)));
        }
        break;

    case ANT_SEARCH_TIMEOUT:
        if (previous_state==ANT_CHANNEL_ID) {

            parent->sendMessage(ANTMessage::setChannelPeriod(number, st->period));
        } else {


            state=previous_state;
        }
        break;

    case ANT_CHANNEL_PERIOD:
        parent->sendMessage(ANTMessage::setChannelFreq(number, st->frequency));
        break;

    case ANT_CHANNEL_FREQUENCY:
        parent->sendMessage(ANTMessage::open(number));
        mi.initialise();
        break;

    case ANT_OPEN_CHANNEL:
        parent->sendMessage(ANTMessage::open(number));
        break;

    default:
        break;
    }
}
