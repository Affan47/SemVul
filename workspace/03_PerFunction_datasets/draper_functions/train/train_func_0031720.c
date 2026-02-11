glusterd_store_is_valid_brickpath (char *volname, char *brick)
{
        char                    brickpath[PATH_MAX] = {0};
        glusterd_brickinfo_t    *brickinfo = NULL;
        glusterd_volinfo_t      *volinfo = NULL;
        int32_t                 ret = 0;
        size_t                  volname_len = strlen (volname);
        xlator_t                *this = NULL;

        this = THIS;
        GF_ASSERT (this);

        ret = glusterd_brickinfo_new_from_brick (brick, &brickinfo);
        if (ret) {
                gf_log (this->name, GF_LOG_WARNING, "Failed to create brick "
                        "info for brick %s", brick);
                ret = 0;
                goto out;
        }
        ret = glusterd_volinfo_new (&volinfo);
        if (ret) {
                gf_log (this->name, GF_LOG_WARNING, "Failed to create volinfo");
                ret = 0;
                goto out;
        }
        if (volname_len >= sizeof (volinfo->volname)) {
                gf_log (this->name, GF_LOG_WARNING, "volume name too long");
                ret = 0;
                goto out;
        }
        memcpy (volinfo->volname, volname, volname_len+1);
        glusterd_store_brickinfopath_set (volinfo, brickinfo, brickpath,
                                                sizeof (brickpath));

        ret = (strlen (brickpath) < _POSIX_PATH_MAX);

out:
        if (brickinfo)
                glusterd_brickinfo_delete (brickinfo);
        if (volinfo)
                glusterd_volinfo_delete (volinfo);

        return ret;
}
