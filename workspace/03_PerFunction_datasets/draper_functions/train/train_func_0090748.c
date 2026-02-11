FileSkipWhite(FILE *fp)
{
    bool bEof = FileSkipWhiteX(fp);
    if (bEof)
        Log(&rLog, LOG_FATAL, "%s", "End-of-file skipping white space");
}
