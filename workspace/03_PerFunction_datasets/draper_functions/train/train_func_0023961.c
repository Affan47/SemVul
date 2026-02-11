ssl_select_method(const char *uhp)
{
	const SSL_METHOD *method;
	char	*cp;

	cp = ssl_method_string(uhp);
	if (cp != NULL) {
		if (equal(cp, "ssl3"))
			method = SSLv3_client_method();
		else if (equal(cp, "tls1"))
			method = TLSv1_client_method();
		else {
			fprintf(stderr, catgets(catd, CATSET, 244,
					"Invalid SSL method \"%s\"\n"), cp);
			method = SSLv23_client_method();
		}
	} else
		method = SSLv23_client_method();
	return method;
}
