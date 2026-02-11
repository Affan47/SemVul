ini_config_file_reopen(struct ini_cfgfile *file_ctx_in,
                           struct ini_cfgfile **file_ctx_out)
{
    int error = EOK;
    struct ini_cfgfile *new_ctx = NULL;

    TRACE_FLOW_ENTRY();

    if ((!file_ctx_in) || (!file_ctx_out)) {
        TRACE_ERROR_NUMBER("Invalid parameter.", EINVAL);
        return EINVAL;
    }


    new_ctx = malloc(sizeof(struct ini_cfgfile));
    if (!new_ctx) {
        TRACE_ERROR_NUMBER("Failed to allocate file ctx.", ENOMEM);
        return ENOMEM;
    }

    new_ctx->file = NULL;


    new_ctx->metadata_flags = file_ctx_in->metadata_flags;


    errno = 0;
    new_ctx->filename = strndup(file_ctx_in->filename, PATH_MAX);
    if (!(new_ctx->filename)) {
        error = errno;
        ini_config_file_destroy(new_ctx);
        TRACE_ERROR_NUMBER("Failed to allocate memory for file path.", error);
        return error;
    }


    error = common_file_init(new_ctx);
    if(error) {
        TRACE_ERROR_NUMBER("Failed to do common init", error);
        ini_config_file_destroy(new_ctx);
        return error;
    }

    *file_ctx_out = new_ctx;
    TRACE_FLOW_EXIT();
    return error;
}
