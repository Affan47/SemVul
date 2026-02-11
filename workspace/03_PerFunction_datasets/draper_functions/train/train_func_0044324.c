replyCurrentJob(const char* leader)
{
    if (curJob->jobid == "default")
	reply(200, "%s (default).", leader);
    else
	reply(200, "%s jobid: %s groupid: %s.", leader,
	    (const char*) curJob->jobid, (const char*) curJob->groupid);
}
