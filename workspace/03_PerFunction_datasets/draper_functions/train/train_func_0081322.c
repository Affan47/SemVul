runfetch(int argc, char **argv){
  char *url;
  int i, rv;
  url = NULL;
  for(i = 2; i < argc; i++){
    if(!url && argv[i][0] == '-'){
      if(!strcmp(argv[i], "-proxy")){
        if(++i >= argc) usage();
        g_pxhost = argv[i];
        if(++i >= argc) usage();
        g_pxport = atoi(argv[i]);
      } else if(!strcmp(argv[i], "-tout")){
        if(++i >= argc) usage();
        g_timeout = atoi(argv[i]);
      } else if(!strcmp(argv[i], "-il")){
        if(++i >= argc) usage();
        g_inputlang = strtolang(argv[i]);
      } else {
        usage();
      }
    } else if(!url){
      url = argv[i];
    } else {
      usage();
    }
  }
  if(!url) usage();
  rv = procfetch(url);
  return rv;
}
