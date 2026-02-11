main(int argc,char *argv[]) {
  char *name = NULL;
  char *wild = "*.*";
  int filesizes = 0;
  int hidden = 0;
  int c;

  while ((c = getopt(argc,argv,":hn:sa"))!=-1) {
    switch(c) {
      case 'h':
        usage(argv[0],0);
        break;
      case 's':
        filesizes = 1;
        break;
      case 'a':
        hidden = 1;
        break;
      case 'n':
        name = strdup(optarg);
        break;
      case ':':
        fprintf(stderr,"Option -%c requires an operand\n",optopt);
        usage(argv[0],1);
        break;
      case '?':
        fprintf(stderr,"Unrecognized option: -%c\n", optopt);
        usage(argv[0],1);
        break;
    }
  }

  if (optind<argc) wild = argv[optind];

  nxt_t *nxt = nxt_open(name);
  if (nxt==NULL) {
    fprintf(stderr,"Could not find NXT\n");
    return 1;
  }

  nxt_list_files(nxt,stdout,wild,filesizes,hidden);

  int ret = nxt_error(nxt);
  if (name!=NULL) free(name);
  nxt_close(nxt);

  return ret;
}
