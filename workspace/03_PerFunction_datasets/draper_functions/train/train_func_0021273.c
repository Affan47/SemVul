glusterd_import_friend_volume (dict_t *vols, size_t count)
{

        int32_t                 ret = -1;
        glusterd_conf_t         *priv = NULL;
        xlator_t                *this = NULL;
        glusterd_volinfo_t      *old_volinfo = NULL;
        glusterd_volinfo_t      *new_volinfo = NULL;

        GF_ASSERT (vols);

        this = THIS;
        GF_ASSERT (this);
        priv = this->private;
        GF_ASSERT (priv);
        ret = glusterd_import_volinfo (vols, count, &new_volinfo);
        if (ret)
                goto out;

        ret = glusterd_volinfo_find (new_volinfo->volname, &old_volinfo);
        if (0 == ret) {
                (void) glusterd_delete_stale_volume (old_volinfo, new_volinfo);
        }

        if (glusterd_is_volume_started (new_volinfo)) {
                (void) glusterd_start_bricks (new_volinfo);
        }

        ret = glusterd_store_volinfo (new_volinfo, GLUSTERD_VOLINFO_VER_AC_NONE);
        ret = glusterd_create_volfiles_and_notify_services (new_volinfo);
        if (ret)
                goto out;

        list_add_tail (&new_volinfo->vol_list, &priv->volumes);
out:
        gf_log ("", GF_LOG_DEBUG, "Returning with ret: %d", ret);
        return ret;
}
