appendRelay(SPtr<TSrvIfaceIface> relay, SPtr<TSrvOptInterfaceID> interfaceID) {
    if (this->RelaysCnt>=HOP_COUNT_LIMIT)
	return false;
    this->Relays[this->RelaysCnt].iface       = relay;
    this->Relays[this->RelaysCnt].ifindex     = relay->getID();
    this->Relays[this->RelaysCnt].interfaceID = interfaceID;
    this->RelaysCnt++;
    return true;
}
