Log(ostream* fout, const char* format, va_list args)
{
    void* addr = buffer_.AllocBuffer();
    if (addr == NULL) return 0;


    LogEntity* log = (LogEntity*)addr;

    log->fout = fout;
    char* buffer = log->data;

    size_t tl = PatchTimeStamp(buffer);
    vsnprintf(buffer + tl, granularity_ - 1, format, args);

    return DoLog(log);
}
