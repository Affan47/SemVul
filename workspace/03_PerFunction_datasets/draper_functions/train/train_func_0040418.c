http_parse_host(host_and_port, host, port)
    const char *host_and_port;
    char *host;
    in_port_t *port;
{
    const char *host_start_p = NULL;
    const char *host_end_p   = NULL;
    const char *port_start_p = NULL;
    size_t host_length;


    *port = 80;
    *host = '\0';


    if (*host_and_port == '[') {


	host_start_p = host_and_port + 1;
	host_end_p = strchr(host_and_port + 1, ']');
	if (host_end_p == NULL)
	    goto error;
	if (*(host_end_p + 1) == ':')
	    port_start_p = host_end_p + 2;
	else if (*(host_end_p + 1) == '\0')
	    port_start_p = NULL;
	else
	    goto error;
    } else {


	const char *colon;

	host_start_p = host_and_port;
	colon = strchr(host_and_port, ':');
	if (colon == NULL) {
	    host_end_p = host_and_port + strlen(host_and_port);
	    port_start_p = NULL;
	} else {
	    host_end_p = colon;
	    port_start_p = colon + 1;
	}
    }


    if (port_start_p != NULL && *port_start_p != '\0') {
	const char *p;
	in_port_t n;

	for (p = port_start_p, n = 0; isdigit(*p); p++)
	    n = n * 10 + (*p - '0');
	if (*p != '\0')
	    goto error;
	*port = n;
    }


    host_length = host_end_p - host_start_p;
    if (host_length == 0 || HTTP_MAX_HOST_NAME_LENGTH < host_length)
	goto error;
    memcpy(host, host_start_p, host_length);
    *(host + host_length) = '\0';

    return 0;


  error:
    *port = 80;
    *host = '\0';
    return -1;
}
