get_archive(ventry *ve, struct archive **archp)
{
    int res;
    char *key;
    struct archive *arch = NULL;
    int neednew;
    int tries;

    res = av_filecache_getkey(ve, &key);
    if(res < 0)
        return res;

    tries = 0;
    do {
        if(tries > 5) {
            av_log(AVLOG_ERROR, "ARCH: Giving up trying to create archive");
            res = -EIO;
            break;
        }
        arch = find_archive(key);

        neednew = 0;
        AV_LOCK(arch->lock);
        if(!(arch->flags & ARCHF_READY))
            res = new_archive(ve, arch);
        else
            res = check_archive(ve, arch, &neednew);
        if(res < 0 || neednew) {
            AV_UNLOCK(arch->lock);
            av_unref_obj(arch);
            av_filecache_set(key, NULL);
        }
        tries ++;
    } while(neednew);

    av_free(key);
    if(res < 0)
        return res;

    *archp = arch;
    return 0;
}
