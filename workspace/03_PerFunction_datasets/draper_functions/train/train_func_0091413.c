vol_open(ventry *ve, int flags, avmode_t mode, void **resp)
{
    int res;
    struct volfs *fs = vol_ventry_volfs(ve);
    struct volentry *ent = vol_ventry_volentry(ve);


    res = vol_open_check(ent->node, flags);
    if(res < 0)
        return res;


    if(ent->node == NULL) {
        res = vol_make_node(fs, ent, mode | AV_IFREG);
        if(res < 0)
            return res;
    }
    else if((flags & AVO_TRUNC) != 0)
        vol_truncate_node(ent->node, 0);

    av_ref_obj(ent->node);

    *resp = ent->node;

    return 0;
}
