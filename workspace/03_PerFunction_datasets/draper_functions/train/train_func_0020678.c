main(int argc,char **argv)
{
    int bflag, ch;
    int opt_zap = 0;

    bflag = 0;
    while ((ch = getopt(argc, argv, "nk:c:h?vZ")) != -1) {
	switch (ch) {
	case 'n': opt_note = 1;break;
	case 'k':
	    if(access(optarg,R_OK)) err(1,"%s",optarg);
	    opt_sign_key_file = optarg;
	    break;
	case 'c':
	    if(access(optarg,R_OK)) err(1,"%s",optarg);
	    opt_sign_cert_file = optarg;
	    break;
	case 'v':
	    printf("%s version %s\n",progname,PACKAGE_VERSION);
	    exit(0);
	case 'Z':
	    opt_zap = 1;
	    break;
	case 'h':
	case '?':
	default:
	    usage();
	    break;
	}
    }
    argc -= optind;
    argv += optind;

    if(opt_sign_cert_file==0) opt_sign_cert_file=opt_sign_key_file;


    if(argc!=1){
	usage();
    }

    if(opt_zap) return remove_signatures(argv[0]);


    if((opt_sign_key_file==0) || (opt_sign_cert_file==0)){
	errx(1,"Both a private key and a certificate must be specified.");
    }


    return afsign(argv[0]);
}
