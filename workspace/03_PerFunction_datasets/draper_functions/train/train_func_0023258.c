auth_withpeer_success(int linkunit,int protocol)
{
	int bit;

	switch (protocol) {
		case PPP_CHAP:
			bit = CHAP_WITHPEER;
			break;
		case PPP_PAP:
			bit = UPAP_WITHPEER;
			break;
		default:
			syslog(LOG_WARNING, "auth_peer_success: unknown protocol %x",protocol);
			bit = 0;
	}


	if ((lns[linkunit].auth_pending &= ~bit) == 0 &&
	     lns[linkunit].phase == PHASE_AUTHENTICATE)
			callback_phase(linkunit);
}
