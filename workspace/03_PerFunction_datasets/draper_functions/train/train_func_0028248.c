printStats() {
	statFreeSpaceOnHeap = myAllocator->getFreeSize();
	int heapUsed = myAllocator->getHeapSize() - statFreeSpaceOnHeap;
	char *statCollectionReasonString;

	switch ((gcReason)statCollectionReason) {
		case reasonStatistics:
			statCollectionReasonString = (char*)"Statistics";
			break;
		case reasonFailedAlloc:
			statCollectionReasonString = (char*)"Failed Alloc";
			break;
		case reasonHighWatermark:
			statCollectionReasonString = (char*)"High Watermark";
			break;
		case reasonDebug:
			statCollectionReasonString = (char*)"Debug";
			break;
		case reasonShift:
			statCollectionReasonString = (char*)"Shift";
			break;
		case reasonEval:
			statCollectionReasonString = (char*)"Evaluation";
			break;
		case reasonForced:
			statCollectionReasonString = (char*)"Forced";
			break;
		default:
			statCollectionReasonString = (char*)"ERROR";
			break;
	}

	stop = clock();
	double elapsed_secs = double(stop - start)/CLOCKS_PER_SEC;
	if (elapsed_secs < shortestGC)
		shortestGC = elapsed_secs;
	if (elapsed_secs > longestGC)
		longestGC = elapsed_secs;
	allGCs += longestGC;

	statLiveObjectCount = myObjectContainer->countElements();
	fprintf(gLogFile, "%8d | %14s | %10d | %14d "
			"| %13d | %10d | %10d | %10d | %4.3f\n", gLineInTrace,
			statCollectionReasonString, statGcNumber, statFreedObjects,
			statLiveObjectCount, heapUsed, statFreeSpaceOnHeap, myGeneration, elapsed_secs);
	fflush(gLogFile);
	if (DEBUG_MODE == 1 && WRITE_ALLOCATION_INFO == 1) {
		myAllocator->printStats();
	}
	if(statCollectionReason == (int)reasonStatistics){
		char fl[80];
		sprintf(fl, "gen%d.log",myGeneration);
		FILE* genfile = fopen(fl,"a");

		fprintf(genfile,"%d\n",heapUsed);
		fflush(genfile);
		fclose(genfile);
	}
	statCollectionReason = (int)reasonStatistics;
}
