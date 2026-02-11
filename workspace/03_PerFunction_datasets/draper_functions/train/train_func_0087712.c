NsTclCacheStatsCmd(ClientData dummy, Tcl_Interp *interp, int argc, char **argv)
{
    Cache *cachePtr;
    char buf[200];
    int entries, flushed, hits, misses, total, hitrate;

    if (argc != 2 && argc != 3) {
	Tcl_AppendResult(interp, "wrong # args: should be \"",
	    argv[0], " cache ?arrayVar?\"", NULL);
	return TCL_ERROR;
    }
    if (GetCache(interp, argv[1], &cachePtr) != TCL_OK) {
    	return TCL_ERROR;
    }
    Ns_MutexLock(&cachePtr->lock);
    entries = cachePtr->entriesTable.numEntries;
    flushed = cachePtr->nflush;
    hits = cachePtr->nhit;
    misses = cachePtr->nmiss;
    total = cachePtr->nhit + cachePtr->nmiss;
    hitrate = (total ? (cachePtr->nhit * 100) / total : 0);
    Ns_MutexUnlock(&cachePtr->lock);

    if (argc == 2) {
	sprintf(buf,
	    "entries: %d  flushed: %d  hits: %d  misses: %d  hitrate: %d",
	    entries, flushed, hits, misses, hitrate);
	Tcl_SetResult(interp, buf, TCL_VOLATILE);
    } else {
    	sprintf(buf, "%d", entries);
    	if (Tcl_SetVar2(interp, argv[2], "entries", buf,
			TCL_LEAVE_ERR_MSG) == NULL) {
	    return TCL_ERROR;
        }
    	sprintf(buf, "%d", flushed);
    	if (Tcl_SetVar2(interp, argv[2], "flushed", buf,
			TCL_LEAVE_ERR_MSG) == NULL) {
	    return TCL_ERROR;
        }
    	sprintf(buf, "%d", hits);
    	if (Tcl_SetVar2(interp, argv[2], "hits", buf,
			TCL_LEAVE_ERR_MSG) == NULL) {
	    return TCL_ERROR;
        }
    	sprintf(buf, "%d", misses);
    	if (Tcl_SetVar2(interp, argv[2], "misses", buf,
			TCL_LEAVE_ERR_MSG) == NULL) {
	    return TCL_ERROR;
        }
    	sprintf(buf, "%d", hitrate);
    	if (Tcl_SetVar2(interp, argv[2], "hitrate", buf,
			TCL_LEAVE_ERR_MSG) == NULL) {
	    return TCL_ERROR;
        }
    }

    return TCL_OK;
}
