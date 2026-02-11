HPDF_FileStream_TellFunc  (HPDF_Stream   stream)
{
    HPDF_INT32 ret;
    HPDF_FILEP fp = (HPDF_FILEP)stream->attr;

    HPDF_PTRACE((" HPDF_FileReader_TellFunc\n"));

    if ((ret = HPDF_FTELL (fp)) < 0) {
        return HPDF_SetError (stream->error, HPDF_FILE_IO_ERROR,
                HPDF_FERROR(fp));
    }

    return ret;
}
