reincarnate (int signum)
{
        int                 ret = 0;
        glusterfs_ctx_t    *ctx = NULL;
        cmd_args_t         *cmd_args = NULL;

        ctx = glusterfs_ctx_get ();
        cmd_args = &ctx->cmd_args;

        if (cmd_args->volfile_server) {
                gf_log ("glusterfsd", GF_LOG_INFO,
                        "Fetching the volume file from server...");
                ret = glusterfs_volfile_fetch (ctx);
        } else {
                gf_log ("glusterfsd", GF_LOG_INFO,
                        "Reloading volfile ...");
                ret = glusterfs_volumes_init (ctx);
        }


        gf_log_logrotate (1);

        if (ret < 0)
                gf_log ("glusterfsd", GF_LOG_ERROR,
                        "volume initialization failed.");

        return;
}
