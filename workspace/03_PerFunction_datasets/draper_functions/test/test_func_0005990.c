ComputeTotalLatencyAux(jack_port_id_t port_index, jack_port_id_t src_port_index, JackConnectionManager* manager, int hop_count)
{
    const jack_int_t* connections = ReadCurrentState()->GetConnections(port_index);
    jack_nframes_t max_latency = 0;
    jack_port_id_t dst_index;

    if (hop_count > 8)
        return GetPort(port_index)->GetLatency();

    for (int i = 0; (i < CONNECTION_NUM_FOR_PORT) && ((dst_index = connections[i]) != EMPTY); i++) {
        if (src_port_index != dst_index) {
            AssertPort(dst_index);
            JackPort* dst_port = GetPort(dst_index);
            jack_nframes_t this_latency = (dst_port->fFlags & JackPortIsTerminal)
                                          ? dst_port->GetLatency()
                                          : ComputeTotalLatencyAux(dst_index, port_index, manager, hop_count + 1);
            max_latency = ((max_latency > this_latency) ? max_latency : this_latency);
        }
    }

    return max_latency + GetPort(port_index)->GetLatency();
}
