initProfilingLogFile(void)
{
    char *prog;

    prog = arenaAlloc(prof_arena, strlen(prog_name) + 1);
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

    if (RtsFlags.CcFlags.doCostCentres == 0 &&
        RtsFlags.ProfFlags.doHeapProfile != HEAP_BY_RETAINER &&
        RtsFlags.ProfFlags.retainerSelector == NULL)
    {

        prof_filename = NULL;
        prof_file = NULL;
    }
    else
    {

        prof_filename = arenaAlloc(prof_arena, strlen(prog) + 6);
        sprintf(prof_filename, "%s.prof", prog);


        if ((prof_file = fopen(prof_filename, "w")) == NULL) {
            debugBelch("Can't open profiling report file %s\n", prof_filename);
            RtsFlags.CcFlags.doCostCentres = 0;


            if (RtsFlags.ProfFlags.doHeapProfile == HEAP_BY_RETAINER)
                RtsFlags.ProfFlags.doHeapProfile = 0;
            return;
        }
    }

    if (RtsFlags.ProfFlags.doHeapProfile) {

	hp_filename = arenaAlloc(prof_arena, strlen(prog) + 6);
	sprintf(hp_filename, "%s.hp", prog);


	if ((hp_file = fopen(hp_filename, "w")) == NULL) {
	    debugBelch("Can't open profiling report file %s\n",
		    hp_filename);
	    RtsFlags.ProfFlags.doHeapProfile = 0;
	    return;
	}
    }
}
