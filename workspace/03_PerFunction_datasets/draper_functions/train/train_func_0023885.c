OpenFD(int filedes, const char *openFlags, TEXTFILE *textFile)
{
    assert(openFlags != NULL);
    assert(textFile != NULL);


    textFile->emptyLine     = TRUE;
    textFile->pendingSpaces = 0;
    textFile->flags = TEXTFILE_FLAG_NONE;
    textFile->file = fdopen(filedes, openFlags);

    if(textFile->file == NULL)
    {
        DEBUG_PRINT(("unable to open fd %d", filedes));
        return FALSE;
    }

    return TRUE;
}
