setOptions(SPtr<TRelParsGlobalOpt> opt) {
    this->ClientUnicast = opt->getClientUnicast();
    this->ServerUnicast = opt->getServerUnicast();
    this->ClientMulticast = opt->getClientMulticast();
    this->ServerMulticast = opt->getServerMulticast();
    this->InterfaceID = opt->getInterfaceID();
}
