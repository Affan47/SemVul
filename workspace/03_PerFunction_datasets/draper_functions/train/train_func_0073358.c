next_arg(struct fuse_opt_context *ctx, const char *opt)
{
    if (ctx->argctr + 1 >= ctx->argc) {
        fprintf(stderr, "fuse: missing argument after `%s'\n", opt);
        return -1;
    }
    ctx->argctr++;
    return 0;
}
