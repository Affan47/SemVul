fwdStartFail(FwdState * fwdState)
{
    ErrorState *err;
    debug(17, 3) ("fwdStartFail: %s\n", storeUrl(fwdState->entry));
    err = errorCon(ERR_CANNOT_FORWARD, HTTP_GATEWAY_TIMEOUT, fwdState->request);
    err->xerrno = errno;
    fwdFail(fwdState, err);
    fwdStateFree(fwdState);
}
