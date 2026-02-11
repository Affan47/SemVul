ns5__ping (struct soap *soap, struct ns5__pingResponse *rep)
{
	char clientdn[256];
	const char *clienthost;
	char func[16];
	struct srm_srv_thread_info *thip = soap->user;

	strcpy (func, "ping");
	get_client_dn (soap, clientdn, sizeof(clientdn));
	clienthost = Cgetnetaddress (-1, &soap->peer, soap->peerlen, &na_key, NULL, NULL, 0, 0);
	if (!clienthost) clienthost = "(unknown)";
	srmlogit (func, "request by %s from %s\n", clientdn, clienthost);

	rep->_Result = true_;
	RETURN (SOAP_OK);
}
