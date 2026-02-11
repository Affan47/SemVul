srmv2_ping(char *endpoint, int timeout)
{
	struct ns1__srmPingResponse_ rep;
	struct ns1__srmPingRequest req;
	struct soap soap;

	srmv2_init (&soap, timeout);

	memset (&req, 0, sizeof(req));

	if (soap_call_ns1__srmPing (&soap, endpoint, "Ping", &req, &rep)) {
		serrno = soap_error2serrno (&soap);
		soap_end (&soap);
		soap_done (&soap);
		return (-1);
	}
	soap_end (&soap);
	soap_done (&soap);
	return (0);
}
