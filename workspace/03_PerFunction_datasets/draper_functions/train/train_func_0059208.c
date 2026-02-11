options_set_defaults() {
    char *s;


    options.interface = get_first_interface();
    if (!options.interface)
        options.interface = "eth0";

    options.filtercode = NULL;
    options.netfilter = 0;
    inet_aton("10.0.1.0", &options.netfilternet);
    inet_aton("255.255.255.0", &options.netfiltermask);
    options.netfilter6 = 0;
    inet_pton(AF_INET6, "fe80::", &options.netfilter6net);
    inet_pton(AF_INET6, "ffff::", &options.netfilter6mask);
    options.link_local = 0;
    options.dnsresolution = 1;
    options.portresolution = 1;
#ifdef NEED_PROMISCUOUS_FOR_OUTGOING
    options.promiscuous = 1;
    options.promiscuous_but_choosy = 1;
#else
    options.promiscuous = 0;
    options.promiscuous_but_choosy = 0;
#endif
    options.showbars = 1;
    options.showports = OPTION_PORTS_OFF;
    options.aggregate_src = 0;
    options.aggregate_dest = 0;
    options.paused = 0;
    options.showhelp = 0;
    options.bandwidth_in_bytes = 0;
    options.sort = OPTION_SORT_DIV2;
    options.screenfilter = NULL;
    options.freezeorder = 0;
    options.linedisplay = OPTION_LINEDISPLAY_TWO_LINE;
    options.screen_offset = 0;
    options.show_totals = 0;
    options.max_bandwidth = 0;
    options.log_scale = 0;
    options.bar_interval = 1;


    s = getenv("HOME");
    if(s != NULL) {
        int i = strlen(s) + 9 + 1;
        options.config_file = xmalloc(i);
        snprintf(options.config_file,i,"%s/.iftoprc",s);
    }
    else {
        options.config_file = xstrdup("iftoprc");
    }
    options.config_file_specified = 0;

}
