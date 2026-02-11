FastaDB_file_is_directory(gchar *path){
    struct stat buf;
    if(stat(path, &buf))
        g_error("Cannot read file [%s]", path);
    return S_ISDIR(buf.st_mode);
    }
