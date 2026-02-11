setJobParameter(Job& job, Token t, u_short value)
{
    if (checkParm(job, t, A_WRITE|A_MODIFY)) {
	for (u_int i = 0, n = N(shortvals); i < n; i++)
	    if (shortvals[i].t == t) {
		if (job.*shortvals[i].p != value) {

		    job.*shortvals[i].p = value;


		    switch (t) {
		    case T_PAGEWIDTH:
		    case T_PAGELENGTH:
		    case T_VRES:
		    case T_HRES:
			flushPreparedDocuments(job);
			break;
		    case T_SCHEDPRI:
			job.pri = job.usrpri;
			break;
		    default:
			break;
		    }
		}
		return (true);
	    }
	parmBotch(t);
    }
    return (false);
}
