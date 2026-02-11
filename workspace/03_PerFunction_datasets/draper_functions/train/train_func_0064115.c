read_options (int argc, char *argv[]) {

     int optchar;
     while(-1 != (optchar=getopt(argc,argv,"a:Ab:c:Cd:Ff:hJ:l:L:m:M:o:w:Pr:t:T:v")))
     {
		switch (optchar) {
		case '?':
			exit(1);

		case 'a':
			cycle_m = atoi(optarg);
			break;

		case 'A' :
			report_aggr_m = TRUE;
			break;

		case 'b':
			thresh_m = (float) atof(optarg);
			break;

		case 'c':
			set_defaults();
			config_m = strdup(optarg);
			read_config(config_m);
			break;

		case 'C' :
			set_defaults();
			break;

		case 'd':
			debug_m = atoi(optarg);
			break;

		case 'F':
			fork_m = TRUE;
			break;

		case 'f':
			filtercmd_m = strdup (optarg);
			break;

		case 'h':
			print_usage();
			exit(0);
			break;

		case 'J':
			lenadj_m = atoi(optarg);
			break;

		case 'm':
			mask_m = atoi(optarg);
			break;

		case 'l':
			mailfoot_m = strdup (optarg);
			break;

		case 'L':
			 parse_ip_range (optarg, &iplist_m, &niplist_m);
                         break;

		case 'M':
			mailto_m = strdup (optarg);
			break;

		case 'o':
			repfname_m = strdup(optarg);
			break;

		case 'w':
			htmlfname_m = strdup(optarg);
			do_html = TRUE;
			break;

		case 'P':
			promisc_m = FALSE;
			break;

		case 'r':
			rcycle_m = atoi(optarg);
			break;

		case 't':
			top_m = atoi(optarg);
			break;

		case 'T':
			mtastring_m = strdup(optarg);
			break;

		case 'v':
			printf ("%s (compiled %s)\n", VERSION_STR, __DATE__);
			printf ("libpcap version %s\n", pcap_version);
			exit(0);
		default:
			exit(1);
		}
	}
}
