zzip_entry_fclose(ZZIP_ENTRY_FILE * file)
{
    if (! file)
        return 0;
    if (file->compressed)
        inflateEnd(&file->zlib);
    zzip_entry_free(file->entry);
    free(file);
    return 0;
}
