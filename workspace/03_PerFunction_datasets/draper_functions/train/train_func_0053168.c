glusterd_store_retrieve_volumes (xlator_t  *this)
{
        int32_t                ret              = 0;
        char                   path[PATH_MAX]   = {0,};
        glusterd_conf_t       *priv             = NULL;
        DIR                   *dir              = NULL;
        struct dirent         *entry            = NULL;
        glusterd_volinfo_t    *volinfo          = NULL;

        GF_ASSERT (this);
        priv = this->private;

        GF_ASSERT (priv);

        snprintf (path, PATH_MAX, "%s/%s", priv->workdir,
                        GLUSTERD_VOLUME_DIR_PREFIX);

        dir = opendir (path);

        if (!dir) {
                gf_log ("", GF_LOG_ERROR, "Unable to open dir %s", path);
                ret = -1;
                goto out;
        }

        glusterd_for_each_entry (entry, dir);

        while (entry) {
                ret = glusterd_store_retrieve_volume (entry->d_name);
                if (ret) {
                        gf_log ("", GF_LOG_ERROR, "Unable to restore "
                                "volume: %s", entry->d_name);
                        goto out;
                }

                ret = glusterd_store_retrieve_rbstate (entry->d_name);
                if (ret) {

                        gf_log ("", GF_LOG_INFO, "Creating a new rbstate "
                                "for volume: %s.", entry->d_name);
                        ret = glusterd_volinfo_find (entry->d_name, &volinfo);
                        ret = glusterd_store_create_rbstate_shandle_on_absence (volinfo);
                        ret = glusterd_store_perform_rbstate_store (volinfo);
                }

                ret = glusterd_store_retrieve_node_state (entry->d_name);
                if (ret) {

                        gf_log ("", GF_LOG_INFO, "Creating a new node_state "
                                "for volume: %s.", entry->d_name);
                        ret = glusterd_volinfo_find (entry->d_name, &volinfo);
                        ret =
                        glusterd_store_create_nodestate_sh_on_absence (volinfo);
                        ret = glusterd_store_perform_node_state_store (volinfo);

                }
                glusterd_for_each_entry (entry, dir);
        }

out:
        if (dir)
                closedir (dir);
        gf_log ("", GF_LOG_DEBUG, "Returning with %d", ret);

        return ret;
}
