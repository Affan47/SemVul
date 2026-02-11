suspendJob(const fxStr& jobid, bool abortActive)
{
    Job* job = Job::getJobByID(jobid);
    if (job && suspendJob(*job, abortActive)) {
	setSuspend(*job);
	FaxRequest* req = readRequest(*job);
	if (req) {
	    updateRequest(*req, *job);
	    delete req;
	}
	return (true);
    } else
	return (false);
}
