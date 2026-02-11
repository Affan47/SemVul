identify(Socket& peercon, Socket& proxycon, HTTPHeader &h, std::string &string)
{


	if (o.use_xforwardedfor) {

		string = h.getXForwardedForIP();

		if (string.length() == 0)
			string = peercon.getPeerIP();
	} else {
		string = peercon.getPeerIP();
	}
	return DGAUTH_OK;
}
