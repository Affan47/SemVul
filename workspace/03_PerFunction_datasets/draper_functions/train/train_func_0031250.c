glusterd_friend_remove_cleanup_vols (uuid_t uuid)
{
        int                     ret = -1;
        glusterd_conf_t         *priv = NULL;
        glusterd_volinfo_t      *volinfo = NULL;
        glusterd_volinfo_t      *tmp_volinfo = NULL;

        priv = THIS->private;
        GF_ASSERT (priv);

        list_for_each_entry_safe (volinfo, tmp_volinfo,
                                  &priv->volumes, vol_list) {
                if (glusterd_friend_contains_vol_bricks (volinfo, uuid)) {
                        gf_log (THIS->name, GF_LOG_INFO,
                                "Deleting stale volume %s", volinfo->volname);
                        ret = glusterd_delete_volume (volinfo);
                        if (ret) {
                                gf_log (THIS->name, GF_LOG_ERROR,
                                        "Error deleting stale volume");
                                goto out;
                        }
                }
        }
        ret = 0;
out:
        gf_log (THIS->name, GF_LOG_DEBUG, "Returning %d", ret);
        return ret;
}
