PortDisconnect(const char* src, const char* dst)
{
    CheckClient("PortDisconnect");
    if (!fIsActivated)
        *fStream << "!!! ERROR !!! Trying to disconnect a port ( " << src << " to " << dst << ") while the client has not been activated !" << endl;
    int res = fClient->PortDisconnect( src, dst);
    int i;
    for (i = (fTotalPortNumber - 1); i >= 0; i--) {
        if (strcmp(fPortList[i].name, src) == 0) {
            if (fPortList[i].IsUnregistered != 0)
                *fStream << "!!! ERROR !!! : Disconnecting port " << src << " previoulsy unregistered !" << endl;
            fPortList[i].IsConnected--;
            *fStream << "disconnecting port " << src << ". ";
            break;
        } else if (strcmp(fPortList[i].name, dst) == 0 ) {
            if (fPortList[i].IsUnregistered != 0)
                *fStream << "!!! ERROR !!! : Disonnecting port  " << dst << " previoulsy unregistered !" << endl;
            fPortList[i].IsConnected--;
            *fStream << "disconnecting port " << dst << ". ";
            break;
        }
    }
    if (i == 0)
        *fStream << "JackClientDebug : PortDisConnect : port was not found in debug database !" << endl;
    if (res != 0)
        *fStream << "Client '" << fClientName << "' try to do PortDisconnect but server return " << res << " ." << endl;

    return res;
}
