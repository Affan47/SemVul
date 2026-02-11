openconnect_set_client_cert (struct openconnect_info *vpninfo, char *cert, char *sslkey)
{
	vpninfo->cert = cert;
	if (sslkey)
		vpninfo->sslkey = sslkey;
	else
		vpninfo->sslkey = cert;
}
