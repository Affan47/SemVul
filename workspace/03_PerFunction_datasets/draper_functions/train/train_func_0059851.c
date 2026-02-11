av_finduid(struct ugidcache *cache, const char *uname, int deflt)
{
    if(uname == NULL || !uname[0])
        return deflt == -1 ? cache->myuid : deflt;

    if(cache->uname == NULL || strcmp(uname, cache->uname) != 0) {
        int res;
        struct passwd pw;
        struct passwd *pwres;
        char *buf = NULL;
        size_t bufsize = 0;

#ifdef HAVE_GETPWNAM_R
        do {
            bufsize += 256;
            buf = av_realloc(buf, bufsize);
            res = getpwnam_r(uname, &pw, buf, bufsize, &pwres);
        } while(res == ERANGE);
#else
	pwres = getpwnam(uname);
#endif

        if(pwres == NULL)
            cache->uid = -1;
        else
            cache->uid = pwres->pw_uid;

        av_free(cache->uname);
        cache->uname = av_strdup(uname);
#ifdef HAVE_GETPWNAM_R
        av_free(buf);
#endif
    }

    if(cache->uid == -1)
        return deflt == -1 ? cache->myuid : deflt;
    else
        return cache->uid;
}
