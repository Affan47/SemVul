RaiseSysError (ml_state_t *msp, const char *altMsg, const char *at)
{
    ml_val_t	    s, atStk, syserror, arg, exn;
    const char	    *msg;
    char	    buf[32];

    if (altMsg != NIL(char *)) {
	msg = altMsg;
	syserror = OPTION_NONE;
    }
    else if ((msg = strerror(errno)) != NIL(char *)) {
	OPTION_SOME(msp, syserror, INT_CtoML(errno))
    }
    else {
	sprintf(buf, "<unknown error %d>", errno);
	msg = buf;
	OPTION_SOME(msp, syserror, INT_CtoML(errno));
    }

#if (defined(DEBUG_OS_INTERFACE) || defined(DEBUG_TRACE_CCALL))
    SayDebug ("RaiseSysError: errno = %d, msg = \"%s\"\n",
	(altMsg != NIL(char *)) ? -1 : errno, msg);
#endif

    s = ML_CString (msp, msg);
    if (at != NIL(char *)) {
	ml_val_t atMsg = ML_CString (msp, at);
	LIST_cons(msp, atStk, atMsg, LIST_nil);
    }
    else
	atStk = LIST_nil;
    REC_ALLOC2 (msp, arg, s, syserror);
    EXN_ALLOC (msp, exn, PTR_CtoML(SysErrId), arg, atStk);

    RaiseMLExn (msp, exn);

    return exn;

}
