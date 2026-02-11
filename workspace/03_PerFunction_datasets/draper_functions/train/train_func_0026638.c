mnt3_resolve_export_subdir (rpcsvc_request_t *req, struct mount3_state *ms,
                            struct mnt3_export *exp)
{
        char            *volume_subdir = NULL;
        int             ret = -EFAULT;

        if ((!req) || (!ms) || (!exp))
                return ret;

        volume_subdir = __volume_subdir (exp->expname, NULL);
        if (!volume_subdir)
                goto err;

        ret = mnt3_resolve_subdir (req, ms, exp, volume_subdir);
        if (ret < 0) {
                gf_log (GF_MNT, GF_LOG_ERROR, "Failed to resolve export dir: %s"
                        , exp->expname);
                goto err;
        }

err:
        return ret;
}
