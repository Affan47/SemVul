PExecute(const char* format, ...)
{
    if (!format)
        return false;

    va_list ap;
    char szQuery [MAX_QUERY_LEN];
    va_start(ap, format);
    int res = vsnprintf(szQuery, MAX_QUERY_LEN, format, ap);
    va_end(ap);

    if (res == -1)
    {
        sLog.outError("SQL Query truncated (and not execute) for format: %s", format);
        return false;
    }

    return Execute(szQuery);
}
