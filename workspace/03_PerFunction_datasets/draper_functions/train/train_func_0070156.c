jack_port_get_all_connections(const jack_client_t* ext_client, const jack_port_t* port)
{
    JackGlobals::CheckContext("jack_port_get_all_connections");

    JackClient* client = (JackClient*)ext_client;
    if (client == NULL) {
        jack_error("jack_port_get_all_connections called with a NULL client");
        return NULL;
    }

    uintptr_t port_aux = (uintptr_t)port;
    jack_port_id_t myport = (jack_port_id_t)port_aux;
    if (!CheckPort(myport)) {
        jack_error("jack_port_get_all_connections called with an incorrect port %ld", myport);
        return NULL;
    } else {
        WaitGraphChange();
        JackGraphManager* manager = GetGraphManager();
        return (manager ? manager->GetConnections(myport) : NULL);
    }
}
