http_proxy_get(struct entry *ent, const char *param, char **retp)
{
    struct statefile *sf = (struct statefile *) av_namespace_get(ent);
    struct avfs *avfs = (struct avfs *) sf->data;
    struct httpfs *fs = (struct httpfs *) avfs->data;
    char *s;

    AV_LOCK(avfs->lock);
    if(fs->proxyname != NULL)
        s = av_stradd(NULL, fs->proxyname, "\n", NULL);
    else
        s = av_strdup("");
    AV_UNLOCK(avfs->lock);

    *retp = s;

    return 0;
}
