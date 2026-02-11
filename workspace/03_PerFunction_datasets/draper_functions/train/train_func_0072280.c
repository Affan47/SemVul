opts(int argc, char **argv){
    int i;
    while((i=getopt(argc,argv,"P:"))!=-1){
        switch(i){
#ifdef WITH_PCAP
        	case 'P':
        		pcap_file=optarg;
        		break;
#endif
            default:
                fprintf(stderr,"unknown option %c\n",optopt);
                usage();
        }
    }
    if(optind < argc)
        host=argv[optind++];
    if(optind < argc)
        desthost=argv[optind++];
    if(optind < argc)
        port=argv[optind++];
    if(host==NULL)
        usage();
    return 0;
}
