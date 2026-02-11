test_heartbeat_extension(gnutls_session_t session)
{
	sprintf(prio_str,
		INIT_STR ALL_CIPHERS ":" ALL_COMP ":" ALL_CERTTYPES ":%s:"
		ALL_MACS ":" ALL_KX ":%s", protocol_str, rest);
	_gnutls_priority_set_direct(session, prio_str);
	gnutls_credentials_set(session, GNUTLS_CRD_CERTIFICATE, xcred);
	gnutls_record_set_max_size(session, 4096);

	gnutls_heartbeat_enable(session, GNUTLS_HB_PEER_ALLOWED_TO_SEND);
	do_handshake(session);

	switch (gnutls_heartbeat_allowed(session, 1)) {
	case 1:
		return TEST_SUCCEED;
	case 0:
		return TEST_FAILED;
	default:
		return TEST_UNSURE;
	}
}
