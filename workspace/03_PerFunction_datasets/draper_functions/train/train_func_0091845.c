zzip_file_stat(ZZIP_FILE * file, ZZIP_STAT * zs)
{
    if (! file)
        return -1;
    zs->d_compr = file->method;
    zs->d_csize = file->csize;
    zs->st_size = file->usize;
    zs->d_name = 0;
    return 0;
}
