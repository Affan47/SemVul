jack_port_by_name(jack_client_t* ext_client, const char* portname)
{
    JackGlobals::CheckContext("jack_port_by_name");

    JackClient* client = (JackClient*)ext_client;
    if (client == NULL) {
        jack_error("jack_port_by_name called with a NULL client");
        return NULL;
    }

    if (portname == NULL) {
        jack_error("jack_port_by_name called with a NULL port name");
        return NULL;
    }

    JackGraphManager* manager = GetGraphManager();
    if (manager) {
        int res = manager->GetPort(portname);
        return (res == NO_PORT) ? NULL : (jack_port_t*)((uintptr_t)res);
    } else {
        return NULL;
    }
}
