Init() {

	ipfull = Uint32toStringIP(ip);

	realport = 0;
	tagcount = 0;
	files = 0;
	users = 0;
	preferences = 0;
	ping = 0;
	description.Clear();
	listname.Clear();
	dynip.Clear();
	failedcount = 0;
	lastpinged = 0;
	lastpingedtime = 0;
	m_dwRealLastPingedTime = 0;
	staticservermember=false;
	maxusers=0;
	m_uTCPFlags = 0;
	m_uUDPFlags = 0;
	challenge = 0;
	softfiles = 0;
	hardfiles = 0;
	m_strVersion = _("Unknown");
	m_uLowIDUsers = 0;
	m_uDescReqChallenge = 0;
	lastdescpingedcout = 0;
	m_auxPorts.Clear();
	m_lastdnssolve = 0;
	m_dnsfailure = false;

	m_dwServerKeyUDP = 0;
	m_bCryptPingReplyPending = false;
	m_dwIPServerKeyUDP = 0;
	m_nObfuscationPortTCP = 0;
	m_nObfuscationPortUDP = 0;

}
