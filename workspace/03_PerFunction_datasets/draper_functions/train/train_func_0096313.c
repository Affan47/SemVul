main(int argc, char **argv)
{
    int c;
    int fd1,fd2;

    while ((c = getopt(argc, argv, "d:hs:v")) > 0) {
	switch (c) {
	case 'd':
	    symbol_dir = optarg;
	    break;
	case 's':
	    scale = atoi(optarg);
	    break;
	case 'v':
	    fprintf(stderr,"sarlacc_scheme ver %s\n", SARVERSION);
	    exit(0);
	    break;
	case 'h':
	default:
	    fprintf(stderr,"Convert Oracd schematics file (16 bit format) to gEDA\n");
	  usage:
	    fprintf(stderr,"\nUsage:   %s [options] infile >outfile\n"
			   "\nOptions:"
			   "\n         -d<dir>  directory for symbols (from sarlacc_sym)"
			   "\n         -h       help"
			   "\n         -s<n>    scale <n>%%, default is %d"
			   "\n         -v       version"
			   "\n\n",
			   argv[0],DEFAULT_SCALE);
	    exit(1);
	    break;
	}
    }

    if( optind+1 != argc )
    {
	goto usage;
    }


    fprintf(stdout,"v %s\n",GEDAVERSION);

    fd1 = open(argv[optind],O_RDONLY);
    if( fd1 < 0 )
    {
	fprintf(stderr,"\nCould not open input file: %s\n",argv[optind]);
	exit(1);
    }
    fd2 = open(argv[optind],O_RDONLY);
    if( fd2 < 0 )
    {
	fprintf(stderr,"\n  Could not open input file part deux\n");
	exit(-1);
    }

    parse_header(fd1,fd2);

    while(parse_block(fd1,fd2));
    fprintf(stderr,"\n Normal End\n");

    return(0);
}
