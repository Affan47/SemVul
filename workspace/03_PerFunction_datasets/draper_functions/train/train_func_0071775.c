ignore_directory_entry(struct dirent *de)
{
    return !strcmp(de->d_name, ".") || !strcmp(de->d_name, "..");
}
