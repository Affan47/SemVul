mkdir_p (char *path, mode_t mode, gf_boolean_t allow_symlinks)
{
        int             i               = 0;
        int             ret             = -1;
        char            dir[PATH_MAX]   = {0,};
        struct stat     stbuf           = {0,};

        strcpy (dir, path);
        i = (dir[0] == '/')? 1: 0;
        do {
                if (path[i] != '/' && path[i] != '\0')
                        continue;

                dir[i] = '\0';
                ret = mkdir (dir, mode);
                if (ret && errno != EEXIST) {
                        gf_log ("", GF_LOG_ERROR, "Failed due to reason %s",
                                strerror (errno));
                        goto out;
                }

                if (ret && errno == EEXIST && !allow_symlinks) {
                        ret = lstat (dir, &stbuf);
                        if (ret)
                                goto out;

                        if (S_ISLNK (stbuf.st_mode)) {
                                ret = -1;
                                gf_log ("", GF_LOG_ERROR, "%s is a symlink",
                                        dir);
                                goto out;
                        }
                }
                dir[i] = '/';

        } while (path[i++] != '\0');

        ret = stat (dir, &stbuf);
        if (ret || !S_ISDIR (stbuf.st_mode)) {
                ret = -1;
                gf_log ("", GF_LOG_ERROR, "Failed to create directory, "
                        "possibly some of the components were not directories");
                goto out;
        }

        ret = 0;
out:

        return ret;
}
