update_connection(jack_port_t *remote_port, int connected,
                  jack_port_t *local_port, jack_port_t *current_port,
                  const char *target_name)
{
    if (connected) {
        if (current_port) {
            return current_port;
        }
        if (target_name) {
            char *aliases[2];
            if (! strcmp(target_name, jack_port_name(remote_port))) {
                return remote_port;
            }
            aliases[0] = alias1;
            aliases[1] = alias2;
            switch (jack_port_get_aliases(remote_port, aliases)) {
            case -1:

                die("jack_port_get_aliases", "Failed to get port aliases");
            case 2:
                if (! strcmp(target_name, alias2)) {
                    return remote_port;
                }

            case 1:
                if (! strcmp(target_name, alias1)) {
                    return remote_port;
                }

            case 0:
                return NULL;
            }

            assert(0);
        }
        return remote_port;
    }
    if (! strcmp(jack_port_name(remote_port), jack_port_name(current_port))) {
        const char **port_names;
        if (target_name) {
            return NULL;
        }
        port_names = jack_port_get_connections(local_port);
        if (port_names == NULL) {
            return NULL;
        }


        current_port = jack_port_by_name(client, port_names[0]);
        jack_free(port_names);
        if (current_port == NULL) {

            die("jack_port_by_name", "failed to get port by name");
        }
    }
    return current_port;
}
