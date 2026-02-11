proxy_socket_recv(rad_listen_t *listener,
			      RAD_REQUEST_FUNP *pfun, REQUEST **prequest)
{
	REQUEST		*request;
	RADIUS_PACKET	*packet;
	RAD_REQUEST_FUNP fun = NULL;
	char		buffer[128];

	packet = rad_recv(listener->fd, 0);
	if (!packet) {
		radlog(L_ERR, "%s", fr_strerror());
		return 0;
	}


	switch(packet->code) {
	case PW_AUTHENTICATION_ACK:
	case PW_ACCESS_CHALLENGE:
	case PW_AUTHENTICATION_REJECT:
		fun = rad_authenticate;
		break;

#ifdef WITH_ACCOUNTING
	case PW_ACCOUNTING_RESPONSE:
		fun = rad_accounting;
		break;
#endif

#ifdef WITH_COA
	case PW_DISCONNECT_ACK:
	case PW_DISCONNECT_NAK:
	case PW_COA_ACK:
	case PW_COA_NAK:
		fun = rad_coa_reply;
		break;
#endif

	default:


		radlog(L_ERR, "Invalid packet code %d sent to a proxy port "
		       "from home server %s port %d - ID %d : IGNORED",
		       packet->code,
		       ip_ntoh(&packet->src_ipaddr, buffer, sizeof(buffer)),
		       packet->src_port, packet->id);
		rad_free(&packet);
		return 0;
	}

	request = received_proxy_response(packet);
	if (!request) {
		rad_free(&packet);
		return 0;
	}

#ifdef WITH_COA


	if ((fun == rad_coa_reply) &&
	    (request->packet->code == request->proxy->code)) {
		fun = rad_coa_recv;
	}
#endif

	rad_assert(fun != NULL);
	*pfun = fun;
	*prequest = request;

	return 1;
}
