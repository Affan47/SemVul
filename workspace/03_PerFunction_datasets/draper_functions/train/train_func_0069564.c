glusterd_volume_brickinfo_get (uuid_t uuid, char *hostname, char *path,
                               glusterd_volinfo_t *volinfo,
                               glusterd_brickinfo_t **brickinfo,
                               gf_path_match_t path_match)
{
        glusterd_brickinfo_t    *brickiter = NULL;
        uuid_t                  peer_uuid = {0};
        int32_t                 ret = -1;

        if (uuid) {
                uuid_copy (peer_uuid, uuid);
        } else {
                ret = glusterd_hostname_to_uuid (hostname, peer_uuid);
                if (ret)
                        goto out;
        }
        ret = -1;
        list_for_each_entry (brickiter, &volinfo->bricks, brick_list) {

                if (uuid_is_null (brickiter->uuid) &&
                    glusterd_resolve_brick (brickiter))
                        goto out;
                if (uuid_compare (peer_uuid, brickiter->uuid))
                        continue;

                if (!strcmp (brickiter->path, path)) {
                        gf_log (THIS->name, GF_LOG_INFO, "Found brick");
                        ret = 0;
                        if (brickinfo)
                                *brickinfo = brickiter;
                        break;
                }
                if (path_match != GF_PATH_PARTIAL)
                        continue;

                if (!fnmatch (path, brickiter->path, FNM_LEADING_DIR) ||
                    !fnmatch (brickiter->path, path, FNM_LEADING_DIR)) {
                        gf_log (THIS->name, GF_LOG_ERROR,
                                "paths %s and %s are recursive",
                                path, brickiter->path);
                        *brickinfo = brickiter;
                        ret = 0;
                        break;
                }
        }

out:
        gf_log ("", GF_LOG_DEBUG, "Returning %d", ret);
        return ret;
}
