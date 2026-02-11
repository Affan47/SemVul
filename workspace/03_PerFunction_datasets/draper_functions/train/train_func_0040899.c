parse_args(int argc, char **argv) {
  int ch;
  dns_servers = strdup(default_dns_servers);
  ip_list_file = NULL;
  listen_addr = strdup(default_listen_addr);
  listen_port = strdup(default_listen_port);
  while ((ch = getopt(argc, argv, "hb:p:s:l:c:y:dmv")) != -1) {
    switch (ch) {
      case 'h':
        printf("%s", help_message);
        exit(0);
      case 'b':
        listen_addr = strdup(optarg);
        break;
      case 'p':
        listen_port = strdup(optarg);
        break;
      case 's':
        dns_servers = strdup(optarg);
        break;
      case 'c':
        chnroute_file = strdup(optarg);
        break;
      case 'l':
        ip_list_file = strdup(optarg);
        break;
      case 'y':
        empty_result_delay = atof(optarg);
        break;
      case 'd':
        bidirectional = 1;
        break;
      case 'm':
        compression = 1;
        break;
      case 'v':
        verbose = 1;
        break;
      default:
        printf("%s", help_message);
        exit(1);
    }
  }
  argc -= optind;
  argv += optind;
  return 0;
}
