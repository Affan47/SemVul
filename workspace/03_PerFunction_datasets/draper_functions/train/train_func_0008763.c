last_modified_time(const string &name)
{
    struct stat m;

    if (stat(name.c_str(), &m) == 0 && (S_IFREG & m.st_mode))
        return m.st_mtime;
    else
        return time(0);
}
