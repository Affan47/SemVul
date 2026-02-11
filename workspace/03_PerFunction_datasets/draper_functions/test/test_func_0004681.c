jack_intclient_request(RequestType type, jack_client_t *client,
		  const char* client_name, jack_options_t options,
		  jack_status_t *status, jack_varargs_t *va)
{
	jack_request_t req;

	memset (&req, 0, sizeof (req));

	if (strlen (client_name) >= sizeof (req.x.intclient.name)) {
		jack_error ("\"%s\" is too long for a JACK client name.\n"
			    "Please use %lu characters or less.",
			    client_name, sizeof (req.x.intclient.name));
		return 0;
	}

	if (va->load_name
	    && (strlen (va->load_name) > sizeof (req.x.intclient.path) - 1)) {
		jack_error ("\"%s\" is too long for a shared object name.\n"
			     "Please use %lu characters or less.",
			    va->load_name, sizeof (req.x.intclient.path) - 1);
		*status |= (JackFailure|JackInvalidOption);
		return 0;
	}

	if (va->load_init
	    && (strlen (va->load_init) > sizeof (req.x.intclient.init) - 1)) {
		jack_error ("\"%s\" is too long for internal client init "
			    "string.\nPlease use %lu characters or less.",
			    va->load_init, sizeof (req.x.intclient.init) - 1);
		*status |= (JackFailure|JackInvalidOption);
		return 0;
	}

	req.type = type;
	req.x.intclient.options = options;
	strncpy (req.x.intclient.name, client_name,
		 sizeof (req.x.intclient.name));
	if (va->load_name)
		strncpy (req.x.intclient.path, va->load_name,
			 sizeof (req.x.intclient.path));
	if (va->load_init)
		strncpy (req.x.intclient.init, va->load_init,
			 sizeof (req.x.intclient.init));

	jack_client_deliver_request (client, &req);

	*status |= req.status;

	if (*status & JackFailure)
		return 0;

	return req.x.intclient.id;
}
