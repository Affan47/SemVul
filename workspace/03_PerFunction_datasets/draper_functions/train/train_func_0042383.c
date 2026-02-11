retrieveInsertInterp(FIS_RESULTSRECORD * results, DUL_ASSOCIATIONKEY ** assoc,
		   DUL_ASSOCIATESERVICEPARAMETERS * params, FIS_HANDLE ** f)
{
    FIS_INTERPRETATIONRECORD *interpPtr,
        interp;
    CONDITION cond,
        rtnCond = 1;

    if (results->Flag & FIS_K_RESULTS_INTERPRETATIONLIST) {
	interpPtr = LST_Head(&results->InterpretationList);
	LST_Position(&results->InterpretationList, interpPtr);
	while (interpPtr != NULL) {
	    printf("%s\n", interpPtr->IntUID);
	    cond = interpretationNGet(assoc, params, interpPtr->IntUID,
				      &interp);
	    if (cond != 1) {
		rtnCond = 0;
		goto ExitPoint;
	    }
	    strcpy(interp.IntUID, interpPtr->IntUID);
	    strcpy(interp.ResUID, results->ResUID);
	    interp.Flag |= (FIS_K_INTERP_RESUID | FIS_K_INTERP_INTUID);
	    if (FIS_Insert(f, FIS_K_INTERPRETATION, &interp) != FIS_NORMAL)
		COND_DumpConditions();

	    interpPtr = LST_Next(&results->InterpretationList);
	}
    }
ExitPoint:
    return rtnCond;
}
