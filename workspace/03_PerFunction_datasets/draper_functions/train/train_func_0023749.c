zzip_fwrite(const void *ptr, zzip_size_t len, zzip_size_t multiply,
            ZZIP_FILE * file)
{
    zzip_ssize_t value = zzip_write(file, ptr, len * multiply);
    if (value == -1)
        value = 0;
    return (zzip_size_t) value;
}
