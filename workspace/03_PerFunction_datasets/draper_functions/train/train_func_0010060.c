NsTclThread(void *arg)
{
    ThreadArg *argPtr = arg;
    Ns_DString ds, *dsPtr;
    int        detached = argPtr->detached;

    if (detached) {
	dsPtr = NULL;
    } else {
	Ns_DStringInit(&ds);
	dsPtr = &ds;
    }


    Ns_WaitForStartup();

    (void) Ns_TclEval(dsPtr, argPtr->server, argPtr->script);
    ns_free(argPtr);
    if (!detached) {
	Ns_ThreadExit(Ns_DStringExport(&ds));
    }
}
