prog_ctx_init (struct prog_ctx *ctx, const char *prog)
{
    ctx->progname = strdup (prog);

    if (!(ctx->edac = edac_handle_create ())) {
        log_fatal (1, "Unable to create EDAC handle\n");
    }
    ctx->verbose = 0;
    ctx->quiet =   0;

    return (0);
}
