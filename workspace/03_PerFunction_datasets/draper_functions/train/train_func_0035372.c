TempProcessDied(ProcTrack* p, int status, int signo, int exitcode
,	int waslogged)
{
	struct tempproc_track *	pt = p->privatedata;

	if (pt->complete) {
		if (debug_level > 1) {
			cl_log(LOG_DEBUG
			,	"%s: Calling 'complete' for temp process %s"
			,	__FUNCTION__, pt->procname);
		}
		pt->complete(pt->userdata, status, signo, exitcode);
	}

	pt->isrunning=FALSE;
	if (pt->runagain) {
		pt->runagain=FALSE;


		G_main_set_trigger(pt->trigger);


	}
	p->privatedata = NULL;
	return;
}
