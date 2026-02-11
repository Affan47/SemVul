gz_getnode(ventry *ve, vfile *base, struct gznode **resp)
{
    int res;
    struct avstat stbuf;
    const int attrmask = AVA_INO | AVA_DEV | AVA_SIZE | AVA_MTIME;
    struct gznode *nod;
    char *key;

    res = av_fgetattr(base, &stbuf, attrmask);
    if(res < 0)
        return res;

    res = av_filecache_getkey(ve, &key);
    if(res < 0)
        return res;

    nod = gz_findnode(ve, key, &stbuf);

    AV_LOCK(nod->lock);
    if(!nod->ready) {
        res = gz_read_header(base, nod);
        if(res < 0)
            av_filecache_set(key, NULL);
    }
    else
        res = 0;
    AV_UNLOCK(nod->lock);
    av_free(key);

    if(res < 0) {
        av_unref_obj(nod);
        return res;
    }

    *resp = nod;
    return 0;
}
