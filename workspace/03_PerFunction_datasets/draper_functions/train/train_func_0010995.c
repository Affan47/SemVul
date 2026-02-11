RegisterAt(Ns_TclTraceProc *proc, void *arg, int when)
{
    NsServer *servPtr;

    servPtr = NsGetInitServer();
    if (servPtr == NULL) {
	return NS_ERROR;
    }
    return Ns_TclRegisterTrace(servPtr->server, proc, arg, when);
}
