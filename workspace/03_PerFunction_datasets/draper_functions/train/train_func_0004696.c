jack_port_type_id(const jack_port_t *port)
{
    JackGlobals::CheckContext("jack_port_type_id");

    uintptr_t port_aux = (uintptr_t)port;
    jack_port_id_t myport = (jack_port_id_t)port_aux;
    if (!CheckPort(myport)) {
        jack_error("jack_port_type_id called an incorrect port %ld", myport);
        return 0;
    } else {
        JackGraphManager* manager = GetGraphManager();
        return (manager ? GetPortTypeId(manager->GetPort(myport)->GetType()) : 0);
    }
}
