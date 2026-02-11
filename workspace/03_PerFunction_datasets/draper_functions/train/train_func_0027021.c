plkr_OpenDBFile
    (
    char*  filename
    )
{
    plkr_DBHandle   handle;
    plkr_Document*  doc;
    int             fp;

#if !defined(WIN32)
    fp = open (filename, O_RDONLY);
#else
    fp = open (filename, O_RDONLY | O_BINARY);
#endif
    if (fp < 0) {
        _plkr_message ("Can't open file %s", filename);
        return NULL;
    }
    handle = (plkr_DBHandle) malloc (sizeof (*handle));
    handle->dbprivate = fp;
    handle->seek = FpSeek;
    handle->read = FpRead;
    handle->free = FpFree;
    handle->size = FpSize;
    doc = plkr_OpenDoc (handle);
    if (doc == NULL)
        close (fp);
    return doc;
}
