process_real_option_group(struct fuse_opt_context *ctx, char *opts)
{
    char *sep;

    do {
        int res;
        sep = strchr(opts, ',');
        if (sep)
            *sep = '\0';
        res = process_gopt(ctx, opts, 1);
        if (res == -1)
            return -1;
        opts = sep + 1;
    } while (sep);

    return 0;
}
