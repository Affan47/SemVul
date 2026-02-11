main(int argc, char **argv){
  const char *tmp;
  int rv;
  if((tmp = getenv("ESTDBGFD")) != NULL) dpdbgfd = atoi(tmp);
  est_proc_env_reset();
  g_progname = argv[0];
  g_sigterm = FALSE;
  g_tasks = cbmapopenex(MINIBNUM);
  cbglobalgc(g_tasks, (void (*)(void *))cbmapclose);
  if(!est_init_net_env()){
    log_print(LL_ERROR, "could not initialize network environment");
    exit(1);
  }
  atexit(est_free_net_env);
  if(argc < 2) usage();
  rv = 0;
  if(!strcmp(argv[1], "init")){
    rv = runinit(argc, argv);
  } else if(!strcmp(argv[1], "crawl")){
    setsignals();
    rv = runcrawl(argc, argv);
  } else if(!strcmp(argv[1], "unittest")){
    rv = rununittest(argc, argv);
  } else if(!strcmp(argv[1], "fetch")){
    rv = runfetch(argc, argv);
  } else {
    usage();
  }
  return rv;
}
