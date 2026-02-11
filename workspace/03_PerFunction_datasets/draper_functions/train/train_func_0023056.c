zzip_tell(ZZIP_FILE * fp)
{
    if (! fp)
        return -1;

    if (! fp->dir)
        return fp->io->fd.tells(fp->fd);


    return (fp->usize - fp->restlen);
}
