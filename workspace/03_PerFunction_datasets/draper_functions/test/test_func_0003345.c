runAllCFinalizers(StgWeak *list)
{
    StgWeak *w;
    Task *task;

    task = myTask();
    if (task != NULL) {
        task->running_finalizers = rtsTrue;
    }

    for (w = list; w; w = w->link) {
	StgArrWords *farr;

	farr = (StgArrWords *)UNTAG_CLOSURE(w->cfinalizer);

	if ((StgClosure *)farr != &stg_NO_FINALIZER_closure)
	    runCFinalizer((void *)farr->payload[0],
	                  (void *)farr->payload[1],
	                  (void *)farr->payload[2],
	                  farr->payload[3]);
    }

    if (task != NULL) {
        task->running_finalizers = rtsFalse;
    }
}
