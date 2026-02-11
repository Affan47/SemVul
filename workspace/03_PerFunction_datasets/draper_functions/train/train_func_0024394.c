glusterd_get_rb_dst_brickinfo (glusterd_volinfo_t *volinfo,
                               glusterd_brickinfo_t **brickinfo)
{
        int32_t                 ret = -1;

        if (!volinfo || !brickinfo)
                goto out;

        *brickinfo = volinfo->dst_brick;

        ret = 0;

out:
        return ret;
}
