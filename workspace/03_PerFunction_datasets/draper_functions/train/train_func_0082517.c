sock_connect(struct sock_addr * const * sas)
{
	int s = -1;


	for (; sas[0] != NULL; sas++) {

		if ((s = socket(sas[0]->ai_family,
		    sas[0]->ai_socktype, 0)) == -1)
			continue;


		if (connect(s, sas[0]->name, sas[0]->namelen) == 0)
			break;


		close(s);
	}


	if (sas[0] == NULL) {
		warn0("Could not connect");
		goto err0;
	}


	if (fcntl(s, F_SETFL, O_NONBLOCK) == -1) {
		warnp("Cannot make connection non-blocking");
		goto err1;
	}


	return (s);

err1:
	close(s);
err0:

	return (-1);
}
