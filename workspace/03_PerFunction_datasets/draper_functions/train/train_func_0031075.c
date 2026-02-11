fwdRestart(void *data)
{
    FwdState *fwdState = data;
    if (fwdState->servers)
	fwdConnectStart(fwdState);
    else
	fwdStartFail(fwdState);
}
