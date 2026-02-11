zzip_seekdir(ZZIP_DIR * dir, zzip_off_t offset)
{
    if (! dir)
        return;

    if (USE_DIRENT && dir->realdir)
    {
        _zzip_seekdir(dir->realdir, offset);
    } else
    {
        dir->hdr = (struct zzip_dir_hdr *)
            (dir->hdr0 ? (char *) dir->hdr0 + (size_t) offset : 0);
    }
}
