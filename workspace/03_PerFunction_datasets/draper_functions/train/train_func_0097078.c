endHeapProfiling(void)
{
    StgDouble seconds;

    if (! RtsFlags.ProfFlags.doHeapProfile) {
        return;
    }

#ifdef PROFILING
    if (doingRetainerProfiling()) {
	endRetainerProfiling();
    }
#endif

#ifdef PROFILING
    if (doingLDVProfiling()) {
	nat t;
	LdvCensusKillAll();
	aggregateCensusInfo();
	for (t = 1; t < era; t++) {
	    dumpCensus( &censuses[t] );
	}
    }
#endif

#ifdef PROFILING
    if (doingLDVProfiling()) {
        nat t;
        for (t = 1; t <= era; t++) {
            freeEra( &censuses[t] );
        }
    } else {
        freeEra( &censuses[0] );
    }
#else
    freeEra( &censuses[0] );
#endif

    stgFree(censuses);

    seconds = mut_user_time();
    printSample(rtsTrue, seconds);
    printSample(rtsFalse, seconds);
    fclose(hp_file);
}
