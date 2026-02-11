NsInitServer(char *server, Ns_ServerInitProc *initProc)
{
    Tcl_HashEntry *hPtr;
    NsServer *servPtr;
    int new;

    hPtr = Tcl_CreateHashEntry(&servers, server, &new);
    if (!new) {
	Ns_Log(Error, "duplicate server: %s", server);
	return;
    }
    servPtr = CreateServer(server);
    Tcl_SetHashValue(hPtr, servPtr);
    Tcl_DStringAppendElement(&serverlist, server);


    RegisterMap(server, "fastpath", "/", Ns_FastPathOp);
    RegisterMaps(server, "fastpath", Ns_FastPathOp);
    RegisterMaps(server, "adp", NsAdpProc);
    RegisterRedirects(server);


    initPtr = servPtr;
    if (initProc != NULL) {
	(*initProc)(server);
    }
    NsLoadModules(server);
    NsTclInitServer(server);
    initPtr = NULL;
}
