ini_config_get_stat(struct ini_cfgfile *file_ctx)
{
    const struct stat *ret;
    TRACE_FLOW_ENTRY();

    if (file_ctx->stats_read) ret = &(file_ctx->file_stats);
    else ret = NULL;

    TRACE_FLOW_EXIT();
    return ret;
}
