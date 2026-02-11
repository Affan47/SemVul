validateMember(Firewall *fw)
{
    string my_host_os = getStr("host_OS");
    string their_host_os = fw->getStr("host_OS");
    string my_platform = getStr("platform");
    string their_platform = fw->getStr("platform");
    if (my_host_os != their_host_os) return false;
    if (my_platform != their_platform) return false;
    if (! Resources::getTargetCapabilityBool(my_host_os, "supports_cluster"))
        return false;


    return true;
}
