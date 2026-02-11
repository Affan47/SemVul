NP_GetEntryPoints(NPPluginFuncs *nppfuncs) {
	if (Log::enabledDbg()) Log::dbg("NP_GetEntryPoints");
	nppfuncs->version       = (NP_VERSION_MAJOR << 8) | NP_VERSION_MINOR;
	nppfuncs->newp          = nevv;
	nppfuncs->destroy       = destroy;
	nppfuncs->getvalue      = getValue;
	nppfuncs->event         = handleEvent;
	nppfuncs->setwindow     = setWindow;
	nppfuncs->urlnotify     = nppUrlNotify;
	nppfuncs->newstream     = nppNewStream;
	nppfuncs->writeready    = nppWriteReady;
	nppfuncs->write         = nppWrite;
	nppfuncs->destroystream = nppDestroyStream;

	return NPERR_NO_ERROR;
}
