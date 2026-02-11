Warning(const char* fmt, ...) {
    if (fDebugLevel < kDLWarning)
        return;
    if (fDebugStream == NULL)
        DelayInit();
    va_list aptr;
    va_start(aptr, fmt);
    WriteLn(fmt, aptr);
    va_end(aptr);
}
