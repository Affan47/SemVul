zzip_file_close(ZZIP_FILE * fp)
{
    auto int self;
    ZZIP_DIR *dir = fp->dir;

    if (fp->method)
        inflateEnd(&fp->d_stream);

    if (dir->cache.locked == NULL)
        dir->cache.locked = &self;

    if (fp->buf32k)
    {
        if (dir->cache.locked == &self && dir->cache.buf32k == NULL)
            dir->cache.buf32k = fp->buf32k;
        else
            free(fp->buf32k);
    }

    if (dir->currentfp == fp)
        dir->currentfp = NULL;

    dir->refcount--;

    memset(fp, 0, sizeof(*fp));

    if (dir->cache.locked == &self && dir->cache.fp == NULL)
        dir->cache.fp = fp;
    else
        free(fp);

    if (dir->cache.locked == &self)
        dir->cache.locked = NULL;

    if (! dir->refcount)
        return zzip_dir_close(dir);
    else
        return 0;
}
