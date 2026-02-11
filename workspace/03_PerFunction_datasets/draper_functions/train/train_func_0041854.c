fillBatch(Batch& batch)
{
    if (! (batch.jobCount() < maxBatchJobs) )
    {
	traceQueue(batch.di, "No more jobs allowed in batch: max %d reached",
		maxBatchJobs);
	sendStart(batch);
	return;
    }

    for (JobIter iter(batch.di.readyQ); iter.notDone(); iter++)
    {
	Job& job(iter);

	FaxRequest* req = readRequest(job);
	if (! req)
	{

	    logError("JOB %s: qfile vanished while on the runq",
		    (const char*)job.jobid);
	    setDead(job);
	    continue;
	}

	if (! isJobSendOK(job, req) )
	    continue;


	if (canJobBatch(batch, job, req) )
	{
	    traceJob(job, "Adding to batch");
	    job.modem = batch.modem;
	    job.remove();
	    processJob(batch, job, req);
	    return;
	}

	delete req;
    }


    sendStart(batch);
}
