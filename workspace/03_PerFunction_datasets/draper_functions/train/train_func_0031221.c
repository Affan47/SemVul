parse_opt (int key, char *arg, struct argp_state *state) {


    ssh_bind sshbind = state->input;
    static int no_default_keys = 0;
    static int rsa_already_set = 0, dsa_already_set = 0, ecdsa_already_set = 0;

    switch (key) {
        case 'n':
            no_default_keys = 1;
            break;
        case 'p':
            ssh_bind_options_set(sshbind, SSH_BIND_OPTIONS_BINDPORT_STR, arg);
            break;
        case 'd':
            ssh_bind_options_set(sshbind, SSH_BIND_OPTIONS_DSAKEY, arg);
            dsa_already_set = 1;
            break;
        case 'k':
            ssh_bind_options_set(sshbind, SSH_BIND_OPTIONS_HOSTKEY, arg);


            no_default_keys = 1;
            break;
        case 'r':
            ssh_bind_options_set(sshbind, SSH_BIND_OPTIONS_RSAKEY, arg);
            rsa_already_set = 1;
            break;
        case 'e':
            ssh_bind_options_set(sshbind, SSH_BIND_OPTIONS_ECDSAKEY, arg);
            ecdsa_already_set = 1;
            break;
        case 'v':
            ssh_bind_options_set(sshbind, SSH_BIND_OPTIONS_LOG_VERBOSITY_STR,
                                 "3");
            break;
        case ARGP_KEY_ARG:
            if (state->arg_num >= 1) {

                argp_usage (state);
            }
            ssh_bind_options_set(sshbind, SSH_BIND_OPTIONS_BINDADDR, arg);
            break;
        case ARGP_KEY_END:
            if (state->arg_num < 1) {

                argp_usage (state);
            }

            if (!no_default_keys) {
                set_default_keys(sshbind,
                                 rsa_already_set,
                                 dsa_already_set,
                                 ecdsa_already_set);
            }

            break;
        default:
            return ARGP_ERR_UNKNOWN;
    }
    return 0;
}
