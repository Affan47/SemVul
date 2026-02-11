read_dir(dirhandle *dh)
{
    struct dirent *de = readdir(*dh);
    return de ? de->d_name : NULL;
}
