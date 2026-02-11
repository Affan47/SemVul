glusterd_op_perform_remove_brick (glusterd_volinfo_t  *volinfo, char *brick,
                                  int force, int *need_migrate)
{
        glusterd_brickinfo_t    *brickinfo = NULL;
        char                    *dup_brick = NULL;
        int32_t                  ret = -1;
        glusterd_conf_t         *priv = NULL;

        GF_ASSERT (volinfo);
        GF_ASSERT (brick);

        priv = THIS->private;
        GF_ASSERT (priv);

        dup_brick = gf_strdup (brick);
        if (!dup_brick)
                goto out;

        ret = glusterd_volume_brickinfo_get_by_brick (dup_brick, volinfo,
                                                      &brickinfo, GF_PATH_COMPLETE);
        if (ret)
                goto out;

        ret = glusterd_resolve_brick (brickinfo);
        if (ret)
                goto out;

        if (!uuid_compare (brickinfo->uuid, priv->uuid)) {

                if (need_migrate)
                        *need_migrate = 1;
        }

        if (force) {
                if (GLUSTERD_STATUS_STARTED == volinfo->status) {
                        ret = glusterd_brick_stop (volinfo, brickinfo);
                        if (ret) {
                                gf_log (THIS->name, GF_LOG_ERROR, "Unable to stop "
                                        "glusterfs, ret: %d", ret);
                                goto out;
                        }
                }
                glusterd_delete_brick (volinfo, brickinfo);
                goto out;
        }

        brickinfo->decommissioned = 1;
out:
        if (dup_brick)
                GF_FREE (dup_brick);

        gf_log ("", GF_LOG_DEBUG, "Returning %d", ret);
        return ret;
}
