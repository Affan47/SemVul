DbgPrint (
    UINT32                  Type,
    char                    *Fmt,
    ...)
{
    va_list                 Args;


    if (!Gbl_DebugFlag)
    {
        return;
    }

    if ((Type == ASL_PARSE_OUTPUT) &&
        (!(AslCompilerdebug)))
    {
        return;
    }

    va_start (Args, Fmt);
    (void) vfprintf (stderr, Fmt, Args);
    va_end (Args);
    return;
}
