usage(FILE* file, jackctl_server_t *server)
{
    fprintf(file, "\n"
            "Usage: jackdmp [ --no-realtime OR -r ]\n"
            "               [ --realtime OR -R [ --realtime-priority OR -P priority ] ]\n"
            "      (the two previous arguments are mutually exclusive. The default is --realtime)\n"
            "               [ --name OR -n server-name ]\n"
            "               [ --timeout OR -t client-timeout-in-msecs ]\n"
            "               [ --loopback OR -L loopback-port-number ]\n"
            "               [ --port-max OR -p maximum-number-of-ports]\n"
            "               [ --slave-backend OR -X slave-backend-name ]\n"
            "               [ --internal-client OR -I internal-client-name ]\n"
            "               [ --verbose OR -v ]\n"
#ifdef __linux__
            "               [ --clocksource OR -c [ c(ycle) | h(pet) | s(ystem) ]\n"
#endif
            "               [ --replace-registry ]\n"
            "               [ --silent OR -s ]\n"
            "               [ --sync OR -S ]\n"
            "               [ --temporary OR -T ]\n"
            "               [ --version OR -V ]\n"
            "         -d master-backend-name [ ... master-backend args ... ]\n"
            "       jackdmp -d master-backend-name --help\n"
            "             to display options for each master backend\n\n");

    if (server) {
        print_server_drivers(server, file);
        print_server_internals(server, file);
    }
}
