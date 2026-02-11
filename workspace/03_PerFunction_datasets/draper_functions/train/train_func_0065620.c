jack_port_get_latency(jack_port_t* port)
{
    JackGlobals::CheckContext("jack_port_get_latency");

    uintptr_t port_aux = (uintptr_t)port;
    jack_port_id_t myport = (jack_port_id_t)port_aux;
    if (!CheckPort(myport)) {
        jack_error("jack_port_get_latency called with an incorrect port %ld", myport);
        return 0;
    } else {
        WaitGraphChange();
        JackGraphManager* manager = GetGraphManager();
        return (manager ? manager->GetPort(myport)->GetLatency() : 0);
    }
}
