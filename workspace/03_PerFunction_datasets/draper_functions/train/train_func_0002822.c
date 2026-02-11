emancipate (glusterfs_ctx_t *ctx, int ret)
{

        if (ctx->daemon_pipe[1] != -1) {
                write (ctx->daemon_pipe[1], (void *) &ret, sizeof (ret));
                close (ctx->daemon_pipe[1]);
                ctx->daemon_pipe[1] = -1;
        }
}
