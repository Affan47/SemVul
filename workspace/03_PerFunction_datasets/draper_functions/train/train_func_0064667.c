glusterd_store_brickinfos (glusterd_volinfo_t *volinfo, int vol_fd)
{
        int32_t                 ret = 0;
        glusterd_brickinfo_t    *brickinfo = NULL;
        int32_t                 brick_count = 0;

        GF_ASSERT (volinfo);

        list_for_each_entry (brickinfo, &volinfo->bricks, brick_list) {
                ret = glusterd_store_brickinfo (volinfo, brickinfo,
                                            brick_count, vol_fd);
                if (ret)
                        goto out;
                brick_count++;
        }
out:
        gf_log (THIS->name, GF_LOG_DEBUG, "Returning %d", ret);
        return ret;
}
