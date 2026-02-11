Ns_TclInitModule(char *server, char *module)
{
    NsServer *servPtr = NsGetServer(server);

    if (servPtr == NULL) {
	return NS_ERROR;
    }
    Tcl_DStringAppendElement(&servPtr->tcl.modules, module);
    return NS_OK;
}
