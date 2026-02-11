GetTwoPorts(const char* src_name, const char* dst_name, jack_port_id_t* port_src, jack_port_id_t* port_dst)
{
    jack_log("JackGraphManager::CheckConnect src_name = %s dst_name = %s", src_name, dst_name);

    if ((*port_src = GetPort(src_name)) == NO_PORT) {
        jack_error("Unknown source port in attempted (dis)connection src_name [%s] dst_name [%s]", src_name, dst_name);
        return -1;
    }

    if ((*port_dst = GetPort(dst_name)) == NO_PORT) {
        jack_error("Unknown destination port in attempted (dis)connection src_name [%s] dst_name [%s]", src_name, dst_name);
        return -1;
    }

    return 0;
}
