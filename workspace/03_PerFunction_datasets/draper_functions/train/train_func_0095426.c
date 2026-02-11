insertNewInterpretation(GATEWAY_EVENT * e, DUL_NETWORKKEY ** network,
	       DMAN_HANDLE ** d, FIS_HANDLE ** f, char *local, char *remote)
{
    CONDITION cond,
        rtnCond = 1;
    FIS_INTERPRETATIONRECORD *interpretationPtr,
        interpretation;

    interpretationPtr = &(e->r.interpretation);
    if (logLevel > 0) {
	fprintf(stdout, "\nAbout to insert new interpretation record from %s\n", remote);
	FIS_DumpRecord(interpretationPtr, stdout);
    }


    memset(&interpretation, 0, sizeof(interpretation));
    cond = FIS_GetOne(f, FIS_K_INTERPRETATION, FIS_K_INTERPRETATION,
		      interpretationPtr->IntUID, 0, &interpretation);
    if (cond == FIS_NORMAL) {
	if (logLevel > 0) {
	    fprintf(stdout, "No need to insert new interpretation record; already exists\n");
	}
	return rtnCond;
    }
    COND_PopCondition();

    if ((interpretationPtr->Flag & FIS_K_INTERP_INTTYPID) == 0) {
	strcpy(interpretationPtr->IntTypID, "REPORT");
	interpretationPtr->Flag |= FIS_K_INTERP_INTTYPID;
    }
    if ((interpretationPtr->Flag & FIS_K_INTERP_INTSTAID) == 0) {
	strcpy(interpretationPtr->IntStaID, "CREATED");
	interpretationPtr->Flag |= FIS_K_INTERP_INTSTAID;
    }
    cond = FIS_Insert(f, FIS_K_INTERPRETATION, interpretationPtr);
    if (cond != FIS_NORMAL) {
	COND_DumpConditions();
	rtnCond = 0;
    }
    return rtnCond;
}
