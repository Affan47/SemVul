setCommon(FaxParam& parm, u_int v)
{
    if (v != this->*parm.pv) {
	if (0 < v && v < parm.NparmNames) {
	    if (command("%s %s", parm.cmd, parm.parmNames[v]) != COMPLETE) {
		printError("%s", (const char*) lastResponse);
		return (false);
	    }
	} else {
	    printError(NLS::TEXT("Bad %s parameter value %u."), parm.cmd, v);
	    return (false);
	}
	this->*parm.pv = v;
    }
    return (true);
}
