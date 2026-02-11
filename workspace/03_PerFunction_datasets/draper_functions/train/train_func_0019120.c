HPDF_FileWriter_New  (HPDF_MMgr        mmgr,
                      const char  *fname)
{
    HPDF_Stream stream;
    HPDF_FILEP fp = HPDF_FOPEN (fname, "wb");

    HPDF_PTRACE((" HPDF_FileWriter_New\n"));

    if (!fp) {
#ifdef UNDER_CE
        HPDF_SetError (mmgr->error, HPDF_FILE_OPEN_ERROR, GetLastError());
#else
        HPDF_SetError (mmgr->error, HPDF_FILE_OPEN_ERROR, errno);
#endif
        return NULL;
    }

    stream = (HPDF_Stream)HPDF_GetMem (mmgr, sizeof(HPDF_Stream_Rec));

    if (stream) {
        HPDF_MemSet (stream, 0, sizeof(HPDF_Stream_Rec));
        stream->sig_bytes = HPDF_STREAM_SIG_BYTES;
        stream->error = mmgr->error;
        stream->mmgr = mmgr;
        stream->write_fn = HPDF_FileWriter_WriteFunc;
        stream->free_fn = HPDF_FileStream_FreeFunc;
        stream->tell_fn = HPDF_FileStream_TellFunc;
        stream->attr = fp;
        stream->type = HPDF_STREAM_FILE;
    }

    return stream;
}
