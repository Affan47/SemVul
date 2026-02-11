getAllowedTypesOfChildren(std::list<std::string> &types_list)
{
    types_list.clear();
    types_list.push_back(Host::TYPENAME);
    types_list.push_back(Firewall::TYPENAME);
    types_list.push_back(Cluster::TYPENAME);
    types_list.push_back(Network::TYPENAME);
    types_list.push_back(NetworkIPv6::TYPENAME);
    types_list.push_back(IPv4::TYPENAME);
    types_list.push_back(IPv6::TYPENAME);
    types_list.push_back(DNSName::TYPENAME);
    types_list.push_back(AddressTable::TYPENAME);
    types_list.push_back(AddressRange::TYPENAME);
    types_list.push_back(FWObjectReference::TYPENAME);
}
