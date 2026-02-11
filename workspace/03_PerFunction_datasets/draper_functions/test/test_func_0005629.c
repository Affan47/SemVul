FlPrintFile (
    UINT32                  FileId,
    char                    *Format,
    ...)
{
    INT32                   Actual;
    va_list                 Args;


    va_start (Args, Format);

    Actual = vfprintf (Gbl_Files[FileId].Handle, Format, Args);
    va_end (Args);

    if (Actual == -1)
    {
        FlFileError (FileId, ASL_MSG_WRITE);
        AslAbort ();
    }
}
