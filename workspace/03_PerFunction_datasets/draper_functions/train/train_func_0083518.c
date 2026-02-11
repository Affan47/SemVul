next_server(const char *caller, isc_sockaddr_t *addr, isc_result_t eresult) {
	char addrbuf[ISC_SOCKADDR_FORMATSIZE];

	isc_sockaddr_format(addr, addrbuf, sizeof(addrbuf));
	fprintf(stderr, "; Communication with %s failed: %s\n",
		addrbuf, isc_result_totext(eresult));
	if (++ns_inuse >= ns_total)
		fatal("could not reach any name server");
	else
		ddebug("%s: trying next server", caller);
}
