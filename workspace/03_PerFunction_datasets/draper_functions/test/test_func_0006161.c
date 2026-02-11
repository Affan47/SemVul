jackctl_server_open(
    jackctl_server *server_ptr,
    jackctl_driver *driver_ptr)
{
    JackSelfConnectMode self_connect_mode;
    JSList * paramlist = NULL;

    try {

        if (!server_ptr || !driver_ptr) {
            return false;
        }

        int rc = jack_register_server(server_ptr->name.str, server_ptr->replace_registry.b);
        switch (rc)
        {
        case EEXIST:
            jack_error("`%s' server already active", server_ptr->name.str);
            goto fail;
        case ENOSPC:
            jack_error("Too many servers already active");
            goto fail;
        case ENOMEM:
            jack_error("No access to shm registry");
            goto fail;
        }

        jack_log("Server `%s' registered", server_ptr->name.str);


        jack_cleanup_shm();
        JackTools::CleanupFiles(server_ptr->name.str);

        if (!server_ptr->realtime.b && server_ptr->client_timeout.i == 0) {
            server_ptr->client_timeout.i = 500;
        }

        switch (server_ptr->self_connect_mode.c)
        {
        case SELF_CONNECT_MODE_ALLOW_CHAR:
            self_connect_mode = JackSelfConnectAllow;
            break;
        case SELF_CONNECT_MODE_FAIL_EXTERNAL_ONLY_CHAR:
            self_connect_mode = JackSelfConnectFailExternalOnly;
            break;
        case SELF_CONNECT_MODE_IGNORE_EXTERNAL_ONLY_CHAR:
            self_connect_mode = JackSelfConnectIgnoreExternalOnly;
            break;
        case SELF_CONNECT_MODE_FAIL_ALL_CHAR:
            self_connect_mode = JackSelfConnectFailAll;
            break;
        case SELF_CONNECT_MODE_IGNORE_ALL_CHAR:
            self_connect_mode = JackSelfConnectIgnoreAll;
            break;
        default:
            self_connect_mode = JACK_DEFAULT_SELF_CONNECT_MODE;
        }


        if (server_ptr->port_max.ui > PORT_NUM_MAX) {
            jack_error("Jack server started with too much ports %d (when port max can be %d)", server_ptr->port_max.ui, PORT_NUM_MAX);
            goto fail;
        }


        server_ptr->engine = new JackServer(
            server_ptr->sync.b,
            server_ptr->temporary.b,
            server_ptr->client_timeout.i,
            server_ptr->realtime.b,
            server_ptr->realtime_priority.i,
            server_ptr->port_max.ui,
            server_ptr->verbose.b,
            (jack_timer_type_t)server_ptr->clock_source.ui,
            self_connect_mode,
            server_ptr->name.str);
        if (server_ptr->engine == NULL)
        {
            jack_error("Failed to create new JackServer object");
            goto fail_unregister;
        }

        if (!jackctl_create_param_list(driver_ptr->parameters, &paramlist)) goto fail_delete;
        rc = server_ptr->engine->Open(driver_ptr->desc_ptr, paramlist);
        jackctl_destroy_param_list(paramlist);
        if (rc < 0)
        {
            jack_error("JackServer::Open failed with %d", rc);
            goto fail_delete;
        }

        return true;

    } catch (std::exception e) {
        jack_error("jackctl_server_open error...");
        jackctl_destroy_param_list(paramlist);
    }

fail_delete:
    delete server_ptr->engine;
    server_ptr->engine = NULL;

fail_unregister:
    jack_log("Cleaning up shared memory");

    jack_cleanup_shm();

    jack_log("Cleaning up files");

    JackTools::CleanupFiles(server_ptr->name.str);

    jack_log("Unregistering server `%s'", server_ptr->name.str);

    jack_unregister_server(server_ptr->name.str);

fail:
    return false;
}
