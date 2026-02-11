parse_args(int argc, char *argv[])
{
	int             ch;
	char           *ep;
#ifdef USE_DEBUG
	int             cls, level;
	int             do_packetlog = 0;
#endif

	while ((ch = getopt(argc, argv, "46ac:dD:f:i:Knp:P:Ll:r:R:v")) != -1) {
		switch (ch) {
		case '4':
			bind_family |= BIND_FAMILY_INET4;
			break;

		case '6':
			bind_family |= BIND_FAMILY_INET6;
			break;

		case 'a':
			acquire_only++;
			break;

		case 'c':
			conf_path = optarg;
			break;

		case 'd':
			debug++;
			break;

#ifdef USE_DEBUG
		case 'D':
			if (sscanf(optarg, "%d=%d", &cls, &level) != 2) {
				if (sscanf(optarg, "A=%d", &level) == 1) {
					for (cls = 0; cls < LOG_ENDCLASS;
					     cls++)
						log_debug_cmd(cls, level);
				} else
					log_print("parse_args: -D argument "
					    "unparseable: %s", optarg);
			} else
				log_debug_cmd(cls, level);
			break;
#endif

		case 'f':
			ui_fifo = optarg;
			break;

		case 'i':
			pid_file = optarg;
			break;

#ifdef USE_POLICY
		case 'K':
			ignore_policy++;
			break;
#endif

		case 'n':
			app_none++;
			break;

		case 'p':
			udp_default_port = optarg;
			break;

		case 'P':
			udp_bind_port = optarg;
			break;

#ifdef USE_DEBUG
		case 'l':
			pcap_file = optarg;


		case 'L':
			do_packetlog++;
			break;
#endif

		case 'r':
			seed = strtoul(optarg, &ep, 0);
			srandom(seed);
			if (*ep != '\0')
				log_fatal("parse_args: invalid numeric arg "
				    "to -r (%s)", optarg);
			regrand = 1;
			break;

		case 'R':
			report_file = optarg;
			break;

		case 'v':
			verbose_logging = 1;
			break;

		case '?':
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;

#ifdef USE_DEBUG
	if (do_packetlog && !pcap_file)
		pcap_file = PCAP_FILE_DEFAULT;
#endif
}
