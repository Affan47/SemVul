TagLogfile(const CONSENT *pCE, char *fmt, ...)
#else
TagLogfile(pCE, fmt, va_alist)
    const CONSENT *pCE;
    char *fmt;
    va_dcl
#endif
{
    va_list ap;
#if PROTOTYPES
    va_start(ap, fmt);
#else
    va_start(ap);
#endif

    if ((pCE == (CONSENT *)0) || (pCE->fdlog == (CONSFILE *)0))
	return;

    FileWrite(pCE->fdlog, FLAGTRUE, "[-- ", -1);
    FileVWrite(pCE->fdlog, FLAGTRUE, fmt, ap);
    FilePrint(pCE->fdlog, FLAGFALSE, " -- %s]\r\n", StrTime((time_t *)0));
    va_end(ap);
}
