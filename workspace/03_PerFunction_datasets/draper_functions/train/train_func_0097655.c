display_transport_state()
{
    jack_transport_state_t ts;
    jack_position_t pos;

    ts = jack_transport_query(client2, &pos);
    switch (ts) {
        case JackTransportStopped:
            Log("Transport is stopped...\n");
            break;
        case JackTransportRolling:
            Log("Transport is rolling...\n");
            break;
        case JackTransportLooping:
            Log("Transport is looping...\n");
            break;
        case JackTransportStarting:
            Log("Transport is starting...\n");
            break;
        case JackTransportNetStarting:
            Log("Transport is starting with network sync...\n");
            break;
    }
}
