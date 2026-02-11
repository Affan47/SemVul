Import(Tcl_Interp *interp, Tcl_DString *dsPtr, int *resultPtr)
{
    Res *resPtr;
    char *str;
    int rlen, clen, ilen;

    if (dsPtr->length < sizeof(Res)) {
	return 0;
    }
    resPtr = (Res *) dsPtr->string;
    str = dsPtr->string + sizeof(Res);
    clen = ntohl(resPtr->clen);
    ilen = ntohl(resPtr->ilen);
    rlen = ntohl(resPtr->rlen);
    if ((clen + ilen + rlen) > (dsPtr->length - sizeof(Res))) {
	return 0;
    }
    if (clen > 0) {
	Tcl_SetErrorCode(interp, str, NULL);
	str += clen;
    }
    if (ilen > 0) {
        Tcl_AddErrorInfo(interp, str);
	str += ilen;
    }
    if (rlen > 0) {
    	Tcl_SetResult(interp, str, TCL_VOLATILE);
    }
    *resultPtr = ntohl(resPtr->code);
    return 1;
}
