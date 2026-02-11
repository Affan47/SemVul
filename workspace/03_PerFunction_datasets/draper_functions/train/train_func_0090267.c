jack_port_tie(jack_port_t* src, jack_port_t* dst)
{
    JackGlobals::CheckContext("jack_port_tie");

    uintptr_t src_aux = (uintptr_t)src;
    jack_port_id_t mysrc = (jack_port_id_t)src_aux;
    if (!CheckPort(mysrc)) {
        jack_error("jack_port_tie called with a NULL src port");
        return -1;
    }
    uintptr_t dst_aux = (uintptr_t)dst;
    jack_port_id_t mydst = (jack_port_id_t)dst_aux;
    if (!CheckPort(mydst)) {
        jack_error("jack_port_tie called with a NULL dst port");
        return -1;
    }
    JackGraphManager* manager = GetGraphManager();
    if (manager && manager->GetPort(mysrc)->GetRefNum() != manager->GetPort(mydst)->GetRefNum()) {
        jack_error("jack_port_tie called with ports not belonging to the same client");
        return -1;
    } else {
        return manager->GetPort(mydst)->Tie(mysrc);
    }
}
