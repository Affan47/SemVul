getAnyRelay() {
    if (this->RelaysCnt==0) {
	Log(Warning) << "No relay interface defined on the " << this->getFullName() << LogEnd;
	return 0;
    }
    return this->Relays[0].iface;
}
