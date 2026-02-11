jack_session_reply(jack_client_t* ext_client, jack_session_event_t *event)
{
    JackGlobals::CheckContext("jack_session_reply");

    JackClient* client = (JackClient*)ext_client;
    jack_log("jack_session_reply ext_client %x client %x ", ext_client, client);
    if (client == NULL) {
        jack_error("jack_session_reply called with a NULL client");
        return -1;
    } else {
        return client->SessionReply(event);
    }
}
