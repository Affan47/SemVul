Codegen_directory_create(gchar *path){
    register mode_t mode = S_IRUSR|S_IWUSR|S_IXUSR
                         | S_IRGRP|S_IXGRP
                         | S_IROTH|S_IXOTH;
    g_warning("Creating codegen directory [%s]", path);
    if(mkdir(path, mode))
        g_error("Could not create directory [%s]", path);
    else
        g_warning("Creating codegen directory [%s]", path);
    return;
    }
