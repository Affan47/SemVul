main(int argc, char** argv)
{

  if(argc < 2){
    fputs(USAGE_MSG, stderr);
    return 1;
  }
  const char* hostname = argv[1];
  int ttl = -1, count = 0x7fff, dsize = 200;
  for(int i=2;argv[i];i++){
    if(argv[i][0] != '-'){
      fprintf(stderr, "Invalid Option: %s\n", argv[i]);
      return 2;
    }
    switch(argv[i][1]){
      case 'c':
        count = atoi(argv[++i]);
        break;
      case 's':
        dsize = atoi(argv[++i]);
        break;
      case 't':
        ttl = atoi(argv[++i]);
        break;
      default:
        fprintf(stderr, "Invalid Option: %s\n", argv[i]);
        return 3;
        break;
    }
  }


  signal(SIGINT, _sigint_handler);


  Pinger icmptalk(hostname, ttl, dsize, count);


  icmptalk.main();

  return 0;
}
