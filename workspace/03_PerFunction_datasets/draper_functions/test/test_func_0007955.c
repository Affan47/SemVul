deleteJob(const char* jobid)
{
    fxStr emsg;
    Job* job = preJobCmd("delete", jobid, emsg);
    if (job) {
	const char* startdir = cwd->pathname;
	if (Sys::chdir("/") < 0) {
	    reply(504, "Cannot change to base spool directory.");
	    return;
	}
	if (job->state != FaxRequest::state_done &&
	  job->state != FaxRequest::state_failed &&
	  job->state != FaxRequest::state_suspended) {
	    reply(504, "Job %s not deleted; use JSUSP first.", jobid);
	    return;
	}
	if (!lockJob(*job, LOCK_EX, emsg)) {
	    reply(504, "Cannot delete job: %s.", (const char*) emsg);
	    return;
	}


	if (job->state == FaxRequest::state_suspended) {
	    for (u_int i = 0, n = job->items.length(); i < n; i++) {
		const FaxItem& fitem = job->items[i];
		switch (fitem.op) {
		case FaxRequest::send_fax:
		    if (sendQueuerACK(emsg, "U%s", (const char*) fitem.item) ||
		      !job->isUnreferenced(i))
			break;

		case FaxRequest::send_tiff_saved:
		case FaxRequest::send_tiff:
		case FaxRequest::send_pdf_saved:
		case FaxRequest::send_pdf:
		case FaxRequest::send_postscript:
		case FaxRequest::send_postscript_saved:
		case FaxRequest::send_pcl:
		case FaxRequest::send_pcl_saved:
		case FaxRequest::send_data:
		    Sys::unlink(fitem.item);
		    break;
		}
	    }
	} else {

	    for (u_int i = 0, n = job->items.length(); i < n; i++) {
		const FaxItem& fitem = job->items[i];
		switch (fitem.op) {
		case FaxRequest::send_tiff_saved:
		case FaxRequest::send_tiff:
		case FaxRequest::send_pdf_saved:
		case FaxRequest::send_pdf:
		case FaxRequest::send_postscript:
		case FaxRequest::send_postscript_saved:
		case FaxRequest::send_pcl:
		case FaxRequest::send_pcl_saved:
		    if (fitem.item.findR(fitem.item.length(), ".cover"))
			Sys::unlink(fitem.item);
		    break;
		}
	    }
	}
	if (Sys::unlink(job->qfile) < 0)
	    reply(504, "Deletion of queue file %s failed.", (const char*) job->qfile);
	if (Sys::chdir(startdir) < 0)
	    reply(504, "Cannot change to %s spool directory.", startdir);
	jobs.remove(job->jobid);
	if (job == curJob)
	    curJob = &defJob;
	delete job;
	replyCurrentJob(fxStr::format("Job %s deleted; current job:", jobid));
    }
}
