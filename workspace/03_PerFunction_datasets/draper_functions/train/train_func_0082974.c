glusterd_is_brickpath_available (uuid_t uuid, char *path)
{
        glusterd_brickinfo_t    *brickinfo = NULL;
        glusterd_volinfo_t      *volinfo   = NULL;
        glusterd_conf_t         *priv      = NULL;
        gf_boolean_t            available  = _gf_false;
        char                    tmp_path[PATH_MAX+1] = {0};
        char                    tmp_brickpath[PATH_MAX+1] = {0};

        priv = THIS->private;

        strncpy (tmp_path, path, PATH_MAX);

        if (!realpath (path, tmp_path)) {
                if (errno != ENOENT) {
                        goto out;
                }

                strncpy(tmp_path,path,PATH_MAX);
        }

        list_for_each_entry (volinfo, &priv->volumes, vol_list) {
                list_for_each_entry (brickinfo, &volinfo->bricks, brick_list) {
                        if (uuid_compare (uuid, brickinfo->uuid))
                                continue;

                        if (!realpath (brickinfo->path, tmp_brickpath)) {
                            if (errno == ENOENT)
                                strncpy (tmp_brickpath, brickinfo->path,
                                         PATH_MAX);
                            else
                                goto out;
                        }

                        if (_is_prefix (tmp_brickpath, tmp_path))
                                goto out;
                }
        }
        available = _gf_true;
out:
        return available;
}
