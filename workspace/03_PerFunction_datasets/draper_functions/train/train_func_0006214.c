directory_list(const char *path, bool recursive,
                   directory_list_callback_t callback, void *user_data)
{
    DIR *dir;
    struct dirent *entry;
    struct stat info;
    int error = 0;
    char entry_path[PATH_MAX];
    bool prune = false;

    if (!(dir = opendir(path))) {
        error = errno;
        return error;
    }

    for (entry = readdir(dir); entry; entry = readdir(dir)) {

        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        error = path_concat(entry_path, sizeof(entry_path),
                            path, entry->d_name);
        if (error != SUCCESS) {
            closedir(dir);


            return error;
        }

        if (lstat(entry_path, &info) < 0) {
            continue;
        }

        prune = !callback(path, entry->d_name, entry_path, &info, user_data);
        if (S_ISDIR(info.st_mode)) {
            if (recursive && !prune) {
                error = directory_list(entry_path, recursive,
                                       callback, user_data);
                if (error != SUCCESS) {
                    closedir(dir);


                    return error;
                }
            }
        }
    }
    error = closedir(dir);
    if (error) {
        return error;
    }
    return SUCCESS;
}
