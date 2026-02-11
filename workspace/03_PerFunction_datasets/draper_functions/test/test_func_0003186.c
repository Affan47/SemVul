glusterd_hooks_create_hooks_directory (char *basedir)
{
        int  ret                                        = -1;
        int  op                                         = GD_OP_NONE;
        int  type                                       = GD_COMMIT_HOOK_NONE;
        char version_dir[PATH_MAX]                      = {0, };
        char path[PATH_MAX]                             = {0, };
        char *cmd_subdir                                = NULL;
        char type_subdir[GD_COMMIT_HOOK_MAX][256]       = {{0, },
                                                           "pre",
                                                           "post"};
        glusterd_conf_t *priv                           = NULL;

        priv = THIS->private;

        snprintf (path, sizeof (path), "%s/hooks", basedir);
        ret = mkdir_if_missing (path);
        if (ret) {
                gf_log (THIS->name, GF_LOG_CRITICAL, "Unable to create %s due"
                         "to %s", path, strerror (errno));
                goto out;
        }

        GLUSTERD_GET_HOOKS_DIR (version_dir, GLUSTERD_HOOK_VER, priv);
        ret = mkdir_if_missing (version_dir);
        if (ret) {
                gf_log (THIS->name, GF_LOG_CRITICAL, "Unable to create %s due "
                        "to %s", version_dir, strerror (errno));
                goto out;
        }

        for (op = GD_OP_NONE+1; op < GD_OP_MAX; op++) {
                cmd_subdir = glusterd_hooks_get_hooks_cmd_subdir (op);
                if (strlen (cmd_subdir) == 0)
                        continue;

                snprintf (path, sizeof (path), "%s/%s", version_dir,
                          cmd_subdir);
                ret = mkdir_if_missing (path);
                if (ret) {
                        gf_log (THIS->name, GF_LOG_CRITICAL,
                                "Unable to create %s due to %s",
                                path, strerror (errno));
                        goto out;
                }

                for (type = GD_COMMIT_HOOK_PRE; type < GD_COMMIT_HOOK_MAX;
                     type++) {
                        snprintf (path, sizeof (path), "%s/%s/%s",
                                  version_dir, cmd_subdir, type_subdir[type]);
                        ret = mkdir_if_missing (path);
                        if (ret) {
                                gf_log (THIS->name, GF_LOG_CRITICAL,
                                        "Unable to create %s due to %s",
                                        path, strerror (errno));
                                goto out;
                        }
                }
        }

        ret = 0;
out:
        return ret;
}
