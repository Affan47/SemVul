main(int argc,char **argv)
{
    int ch;
    const char *opt_x=0;


#ifdef HAVE_SRANDOMEDEV
    srandomdev();
#endif
    OpenSSL_add_all_digests();


    while ((ch = getopt(argc, argv, "x:h?V")) != -1) {
	switch (ch) {
	case 'h':
	case '?':
	default:
	    usage();
	    break;
	case 'x': opt_x = optarg; break;
	case 'V':
	    printf("%s version %s\n",progname,PACKAGE_VERSION);
	    exit(0);
	}
    }
    argc -= optind;
    argv += optind;

    if(argc!=1){
	usage();
    }

    if(opt_x){
	diskprint_verify(argv[0],opt_x);
	return(0);
    }


    printf("<?xml version='1.0' encoding='UTF-8'?>\n");
    printf("<diskprints>\n");
    while(*argv){
	if(opt_x){
	    diskprint_verify(*argv,opt_x);
	}
	else {
	    diskprint(*argv);
	}
	argv++;
	argc--;
    }
    printf("</diskprints>\n");
    exit(0);
}
