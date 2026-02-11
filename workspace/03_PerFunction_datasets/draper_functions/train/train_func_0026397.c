initProfiling2 (void)
{
    char *prog;

    prog = stgMallocBytes(strlen(prog_name) + 1, "initProfiling2");
    strcpy(prog, prog_name);
#ifdef mingw32_HOST_OS

    {
        char *suff;
        suff = strrchr(prog,'.');
        if (suff != NULL && !strcmp(suff,".exe")) {
            *suff = '\0';
        }
    }
#endif

  if (RtsFlags.ProfFlags.doHeapProfile) {

    hp_filename = stgMallocBytes(strlen(prog) + 6, "hpFileName");
    sprintf(hp_filename, "%s.hp", prog);


    if ((hp_file = fopen(hp_filename, "w")) == NULL) {
      debugBelch("Can't open profiling report file %s\n",
	      hp_filename);
      RtsFlags.ProfFlags.doHeapProfile = 0;
      return;
    }
  }

  stgFree(prog);

  initHeapProfiling();
}
