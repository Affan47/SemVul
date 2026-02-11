stopTimeout(const char* whichdir)
{
    timer.stopTimeout();
    if (timeout = timer.wasTimeout())
	traceModemOp("TIMEOUT: %s", whichdir);
}
