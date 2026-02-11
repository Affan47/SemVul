get_filesystem_info(double &total_space, double &free_space, const char* const path) {
#ifdef STATFS
    struct STATFS fs_info;

    int retval = STATFS(path, &fs_info);
    if (retval) {
#ifndef _USING_FCGI_
        perror("statvfs");
#else
        FCGI::perror("statvfs");
#endif
        return ERR_STATFS;
    }
#if HAVE_SYS_STATVFS_H
    total_space = (double)fs_info.f_frsize * (double)fs_info.f_blocks;
    free_space = (double)fs_info.f_frsize * (double)fs_info.f_bavail;
#else
    total_space = (double)fs_info.f_bsize * (double)fs_info.f_blocks;
    free_space = (double)fs_info.f_bsize * (double)fs_info.f_bavail;
#endif
#else
#error Need to specify a method to obtain free/total disk space
#endif
#endif
    return 0;
}
