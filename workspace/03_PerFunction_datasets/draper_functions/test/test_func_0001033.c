setRecordsOriginFile(const char *fname)
{
    if (recordsOriginFile != NULL)
        delete[] recordsOriginFile;
    if (fname != NULL)
    {
        recordsOriginFile = new char[strlen(fname) + 1];
        strcpy(recordsOriginFile, fname);
    } else
        recordsOriginFile = NULL;
}
