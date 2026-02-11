FCGI_fseek(FCGI_FILE *fp, long offset, int whence)
{
    if(fp->stdio_stream)
        return fseek(fp->stdio_stream, offset, whence);
    else {
        OS_SetErrno(ESPIPE);
        return -1;
    }
}
