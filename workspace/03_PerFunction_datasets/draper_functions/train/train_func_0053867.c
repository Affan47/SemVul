cmsSignalError(cmsContext ContextID, cmsUInt32Number ErrorCode, const char *ErrorText, ...)
{
    va_list args;
    char Buffer[MAX_ERROR_MESSAGE_LEN];
    _cmsLogErrorChunkType* lhg;


    va_start(args, ErrorText);
    vsnprintf(Buffer, MAX_ERROR_MESSAGE_LEN-1, ErrorText, args);
    va_end(args);


    lhg = (_cmsLogErrorChunkType*) _cmsContextGetClientChunk(ContextID, Logger);
    if (lhg ->LogErrorHandler) {
        lhg ->LogErrorHandler(ContextID, ErrorCode, Buffer);
    }
}
