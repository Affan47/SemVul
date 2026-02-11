CheckPortsConnect(int refnum, jack_port_id_t src, jack_port_id_t dst)
{
    JackPort* src_port = fGraphManager->GetPort(src);
    JackPort* dst_port = fGraphManager->GetPort(dst);

    jack_log("JackEngine::CheckPortsConnect(ref = %d, src = %d, dst = %d)", refnum, src_port->GetRefNum(), dst_port->GetRefNum());

    int src_self = src_port->GetRefNum() == refnum ? 1 : 0;
    int dst_self = dst_port->GetRefNum() == refnum ? 1 : 0;

    jack_log("src_self is %s", src_self ? "true" : "false");
    jack_log("dst_self is %s", dst_self ? "true" : "false");


    switch (fSelfConnectMode)
    {
    case JackSelfConnectFailExternalOnly:
        if (src_self + dst_self == 1)
        {
            jack_info("rejecting port self connect request to external port (%s -> %s)", src_port->GetName(), dst_port->GetName());
            return -1;
        }

        return 1;

    case JackSelfConnectIgnoreExternalOnly:
        if (src_self + dst_self == 1)
        {
            jack_info("ignoring port self connect request to external port (%s -> %s)", src_port->GetName(), dst_port->GetName());
            return 0;
        }

        return 1;

    case JackSelfConnectFailAll:
        if (src_self + dst_self != 0)
        {
            jack_info("rejecting port self connect request (%s -> %s)", src_port->GetName(), dst_port->GetName());
            return -1;
        }

        return 1;

    case JackSelfConnectIgnoreAll:
        if (src_self + dst_self != 0)
        {
            jack_info("ignoring port self connect request (%s -> %s)", src_port->GetName(), dst_port->GetName());
            return 0;
        }

        return 1;

    case JackSelfConnectAllow:
        return 1;
    }

    return 1;
}
