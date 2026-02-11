setJobParameter(Job& job, Token t, bool b)
{
    if (checkParm(job, t, A_WRITE|A_MODIFY)) {
	switch (t) {
	case T_USE_ECM:
	    job.desiredec = b;
	    return (true);
	case T_USE_TAGLINE:
	    job.desiredtl = b;
	    return (true);
	case T_USE_XVRES:
	    job.usexvres = b;
	    return (true);
	case T_USE_CONTCOVER:
	    job.useccover = b;
	    return (true);
	default:
	    break;
	}
	parmBotch(t);
    }
    return (false);
}
