glusterd_store_perform_brick_store (glusterd_brickinfo_t *brickinfo)
{
        int                         fd = -1;
        int32_t                     ret = -1;
        GF_ASSERT (brickinfo);

        fd = gf_store_mkstemp (brickinfo->shandle);
        if (fd <= 0) {
                ret = -1;
                goto out;
        }

        ret = glusterd_store_brickinfo_write (fd, brickinfo);
        if (ret)
                goto out;

out:
        if (ret && (fd > 0))
                gf_store_unlink_tmppath (brickinfo->shandle);
        if (fd > 0)
                close (fd);
        gf_log (THIS->name, GF_LOG_DEBUG, "Returning %d", ret);
        return ret;
}
