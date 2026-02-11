getNonBlankMailbox(fxStr& s)
{
    for (u_int i = 0, n = jobs->length(); i < n; i++) {
	SNPPJob& job = (*jobs)[i];
	if (job.getMailbox() != "") {
	    s = job.getMailbox();
	    return (true);
	}
    }
    return (false);
}
