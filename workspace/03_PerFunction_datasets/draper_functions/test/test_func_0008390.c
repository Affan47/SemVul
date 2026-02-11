get_parent_dir_time_attrib(char *filepath, char *parentdirbuf, int bufsize, struct timeval *tv)
{
    struct stat64 statbuf;

    extract_dirpath(filepath, parentdirbuf, bufsize);

    if (lstat64(parentdirbuf, &statbuf)!=0)
    {   sysprintf("cannot lstat64(%s)\n", parentdirbuf);
        return -1;
    }

    if (!S_ISDIR(statbuf.st_mode))
    {   sysprintf("error: [%s] is not a directory\n", parentdirbuf);
        return -1;
    }


    tv[0].tv_usec=0;
    tv[0].tv_sec=statbuf.st_atime;
    tv[1].tv_usec=0;
    tv[1].tv_sec=statbuf.st_mtime;

    return 0;
}
