mkdir_if_missing (char *path)
{
        struct stat st = {0,};
        int        ret = 0;

        ret = mkdir (path, 0777);
        if (!ret || errno == EEXIST)
                ret = stat (path, &st);
        if (ret == -1 || !S_ISDIR (st.st_mode))
                gf_log ("", GF_LOG_WARNING, "Failed to create the"
                        " directory %s", path);

        return ret;
}
