av_check_version(const char *modname, const char *name,
                       int version, int need_ver, int provide_ver)
{
    if(version < need_ver || version > provide_ver) {
        if(version < need_ver)
            av_log(AVLOG_WARNING,
                     "%s: %s has version %i. Needs to be at least %i.",
                     modname, name, version, need_ver);
        else
            av_log(AVLOG_WARNING,
                     "%s: %s has version %i. Cannot handle above %i.",
                     modname, name, version, provide_ver);

        return -ENODEV;
    }

    return 0;
}
