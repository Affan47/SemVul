check_data_dir(const char* data_dir)
{
    gboolean ret = FALSE;
    char* dir_path = g_build_filename(data_dir, "thumbnailers", NULL);
    struct stat statbuf;
    if(stat(dir_path, &statbuf) == 0)
    {
        if(statbuf.st_mtime > last_loaded_time)
            ret = TRUE;
    }
    g_free(dir_path);
    return ret;
}
