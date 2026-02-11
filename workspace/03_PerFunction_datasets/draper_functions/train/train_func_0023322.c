prepareStart(Batch& batch, Job& job, FaxRequest* req)
{
    traceQueue(job, "PREPARE START");
    abortPrepare = false;
    pid_t pid = fork();
    switch (pid) {
    case 0:


	signal(SIGTERM, fxSIGHANDLER(faxQueueApp::prepareCleanup));
	signal(SIGINT, fxSIGHANDLER(faxQueueApp::prepareCleanup));
	_exit(prepareJob(job, *req, batch));

    case -1:
	job.remove();
	delayJob(job, *req, Status(340, "Could not fork to prepare job for transmission"),
	    Sys::now() + random() % requeueInterval);
	delete req;
	fillBatch(batch);
    default:
	batch.startPrepare(job, pid);
	job.pid = pid;
	delete req;
	Trigger::post(Trigger::JOB_PREP_BEGIN, job);
	break;
    }
}
