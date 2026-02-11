is_gf_log_command (xlator_t *this, const char *name, char *value)
{
        xlator_t       *trav        = NULL;
        char            key[1024]   = {0,};
        int             ret         = -1;
        int             log_level   = -1;
        gf_boolean_t    syslog_flag = 0;
        glusterfs_ctx_t *ctx        = NULL;

        if (!strcmp ("trusted.glusterfs.syslog", name)) {
                ret = gf_string2boolean (value, &syslog_flag);
                if (ret) {
                        ret = EOPNOTSUPP;
                        goto out;
                }
                if (syslog_flag)
                        gf_log_enable_syslog ();
                else
                        gf_log_disable_syslog ();

                goto out;
        }

        if (fnmatch ("trusted.glusterfs*set-log-level", name, FNM_NOESCAPE))
                goto out;

        log_level = glusterd_check_log_level (value);
        if (log_level == -1) {
                ret = EOPNOTSUPP;
                goto out;
        }


        if (!strcmp (name, "trusted.glusterfs.set-log-level")) {

                gf_log ("glusterfs", gf_log_get_loglevel(),
                        "setting log level to %d (old-value=%d)",
                        log_level, gf_log_get_loglevel());
                gf_log_set_loglevel (log_level);
                ret = 0;
                goto out;
        }

        if (!strcmp (name, "trusted.glusterfs.fuse.set-log-level")) {

                gf_log (this->name, gf_log_get_xl_loglevel (this),
                        "setting log level to %d (old-value=%d)",
                        log_level, gf_log_get_xl_loglevel (this));
                gf_log_set_xl_loglevel (this, log_level);
                ret = 0;
                goto out;
        }

        ctx = glusterfs_ctx_get();
        if (!ctx)
                goto out;
        if (!ctx->active)
                goto out;
        trav = ctx->active->top;

        while (trav) {
                snprintf (key, 1024, "trusted.glusterfs.%s.set-log-level",
                          trav->name);
                if (fnmatch (name, key, FNM_NOESCAPE) == 0) {
                        gf_log (trav->name, gf_log_get_xl_loglevel (trav),
                                "setting log level to %d (old-value=%d)",
                                log_level, gf_log_get_xl_loglevel (trav));
                        gf_log_set_xl_loglevel (trav, log_level);
                        ret = 0;
                }
                trav = trav->next;
        }
out:
        return ret;
}
