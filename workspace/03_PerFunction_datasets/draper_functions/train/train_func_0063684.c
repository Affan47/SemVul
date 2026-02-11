disconnect(int duringPortDisconnect)
{
    if (!p_remoteSysPort) {
        cout << "-W- Trying to disconenct non connected system port." << endl;
        return(1);
    }

    if (p_remoteSysPort->p_remoteSysPort != this) {
        cout << "-W- Remote port does not point back! Disconnecting self only."
                << endl;
        p_remoteSysPort = NULL;
        return(1);
    }

    IBSysPort *p_remSysPort = p_remoteSysPort;
    p_remoteSysPort->p_remoteSysPort = NULL;
    p_remoteSysPort = NULL;
    if (FabricUtilsVerboseLevel & FABU_LOG_VERBOSE)
        cout << "-I- Disconnected system port:" << name
            << " from:" << p_remSysPort->name << endl;


    if (p_nodePort && ! duringPortDisconnect) return(p_nodePort->disconnect(1));
    return(0);
}
