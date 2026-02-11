setupModem(bool isSend)
{
    modem = NULL;
    if (!ModemServer::setupModem(isSend))
	return (false);
    if (getModem()->isFaxModem()) {
	modem = (FaxModem*) ModemServer::getModem();
	modem->setLID(localIdentifier);
    }
    return (true);
}
