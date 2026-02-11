get_path_to_volume(char *newvolbuf, int bufsize, char *basepath, long curvol)
{
    char prefix[PATH_MAX];
    int pathlen;

    if ((pathlen=strlen(basepath))<4)
    {   errprintf("archive has an invalid basepath: [%s]\n", basepath);
        return -1;
    }

    if (curvol==0)
    {
        if (realpath(basepath, newvolbuf)!=newvolbuf)
            snprintf(newvolbuf, bufsize, "%s", basepath);
    }
    else
    {
        memset(prefix, 0, sizeof(prefix));
        memcpy(prefix, basepath, pathlen-2);
        snprintf(newvolbuf, bufsize, "%s%.2ld", prefix, (long)curvol);
    }

    return 0;
}
