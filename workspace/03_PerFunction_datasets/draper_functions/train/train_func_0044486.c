ajFileIsFile(const AjPFile file)
{
#if defined(AJ_IRIXLF)
    struct stat64 buf;
#else
    struct stat buf;
#endif

    if(
#if defined(AJ_IRIXLF)
        !fstat64(fileno(file->fp), &buf)
#else
        !fstat(fileno(file->fp), &buf)
#endif
       )
        if((ajuint)buf.st_mode & AJ_FILE_R)
            return ajTrue;

    return ajFalse;
}
