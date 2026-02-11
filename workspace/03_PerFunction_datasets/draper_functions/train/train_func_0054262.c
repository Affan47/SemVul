eb_fix_directory_name(path, directory_name)
    const char *path;
    char *directory_name;
{
    struct dirent *entry;
    DIR *dir;


    dir = opendir(path);
    if (dir == NULL)
        goto failed;

    for (;;) {


        entry = readdir(dir);
        if (entry == NULL)
            goto failed;

	if (strcasecmp(entry->d_name, directory_name) == 0)
	    break;
    }

    strcpy(directory_name, entry->d_name);
    closedir(dir);
    return EB_SUCCESS;


  failed:
    if (dir != NULL)
	closedir(dir);
    return EB_ERR_BAD_DIR_NAME;
}
