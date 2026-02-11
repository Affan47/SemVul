jack_client_open_aux(const char* client_name, jack_options_t options, jack_status_t* status, va_list ap)
{
    jack_varargs_t va;
    jack_status_t my_status;
    JackClient* client;

    if (client_name == NULL) {
        jack_error("jack_client_open called with a NULL client_name");
        return NULL;
    }

    jack_log("jack_client_open %s", client_name);

    if (status == NULL)
        status = &my_status;
    *status = (jack_status_t)0;


    if ((options & ~JackOpenOptions)) {
        int my_status1 = *status | (JackFailure | JackInvalidOption);
        *status = (jack_status_t)my_status1;
        return NULL;
    }


    jack_varargs_parse(options, ap, &va);

    JackLibGlobals::Init();

    if (try_start_server(&va, options, status)) {
        jack_error("jack server is not running or cannot be started");
        JackLibGlobals::Destroy();
        return 0;
    }

    if (JACK_DEBUG) {
        client = new JackDebugClient(new JackLibClient(GetSynchroTable()));
    } else {
        client = new JackLibClient(GetSynchroTable());
    }

    int res = client->Open(va.server_name, client_name, va.session_id, options, status);
    if (res < 0) {
        delete client;
        JackLibGlobals::Destroy();
        int my_status1 = (JackFailure | JackServerError);
        *status = (jack_status_t)my_status1;
        return NULL;
    } else {
        return (jack_client_t*)client;
    }
}
