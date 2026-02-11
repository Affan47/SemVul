hfile_destroy(hFILE *fp)
{
    int save = errno;
    if (fp) free(fp->buffer);
    free(fp);
    errno = save;
}
