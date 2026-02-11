NsWaitDriversShutdown(Ns_Time *toPtr)
{
    Driver *drvPtr = firstDrvPtr;
    int status = NS_OK;

    while (drvPtr != NULL) {
	Ns_MutexLock(&drvPtr->lock);
        while (!(drvPtr->flags & DRIVER_STOPPED) && status == NS_OK) {
	    status = Ns_CondTimedWait(&drvPtr->cond, &drvPtr->lock, toPtr);
	}
	Ns_MutexUnlock(&drvPtr->lock);
	if (status != NS_OK) {
	    Ns_Log(Warning, "driver: shutdown timeout: %s", drvPtr->module);
	} else {
	    Ns_Log(Notice, "driver: stopped: %s", drvPtr->module);
	    Ns_ThreadJoin(&drvPtr->thread, NULL);
	    drvPtr->thread = NULL;
	}
	drvPtr = drvPtr->nextPtr;
    }
}
