DXSetError(ErrorCode code, char *message, ...)
{
    va_list arg;
    int usedmessfile;
    int offset = 0;

    message = translate(message, &usedmessfile);


    _ErrorCode = code;


#if DEBUGGED
    if (!usedmessfile) {
        strcpy(_ErrorMessage, TAG);
	offset = TAGLEN;
    }
#endif
    va_start(arg,message);
    vsprintf(_ErrorMessage+offset, message, arg);
    va_end(arg);


    if (!state || state->error_exit == 1)
	DXPrintError(NULL);
    else if (state->error_exit >= 2)
	DXErrorExit(NULL);

    return ERROR;
}
