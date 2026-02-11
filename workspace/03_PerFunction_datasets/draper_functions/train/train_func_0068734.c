glusterd_defrag_start_validate (glusterd_volinfo_t *volinfo, char *op_errstr,
                                size_t len)
{
        int     ret = -1;

        if (glusterd_is_defrag_on (volinfo)) {
                gf_log ("glusterd", GF_LOG_DEBUG,
                        "rebalance on volume %s already started",
                        volinfo->volname);
                snprintf (op_errstr, len, "Rebalance on %s is already started",
                          volinfo->volname);
                goto out;
        }

        if (glusterd_is_rb_started (volinfo) ||
            glusterd_is_rb_paused (volinfo)) {
                gf_log ("glusterd", GF_LOG_DEBUG,
                        "Rebalance failed as replace brick is in progress on volume %s",
                        volinfo->volname);
                snprintf (op_errstr, len, "Rebalance failed as replace brick is in progress on "
                          "volume %s", volinfo->volname);
                goto out;
        }
        ret = 0;
out:
        gf_log ("glusterd", GF_LOG_DEBUG, "Returning %d", ret);
        return ret;
}
