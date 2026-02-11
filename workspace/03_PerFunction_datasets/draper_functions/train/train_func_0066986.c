macpdp_tag_thread(void *args)
{
    struct pdp_job_arg *arg = (struct pdp_job_arg *) args;
    pdp_ctx_t *ctx;
    pdp_macpdp_ctx_t *p;
    unsigned char *tag = NULL;
    unsigned int tag_len = 0;
    unsigned char *buf = NULL;
    unsigned int i, block;
    int *ret = NULL;

    if (!arg || !arg->ctx || !arg->key || !arg->file ||
                !arg->tags || !arg->numblocks)
        goto cleanup;

    ctx = arg->ctx;
    p = ctx->macpdp_param;

#ifdef _PDP_DEBUG
    DEBUG(1, "\n Tagging %d blocks", arg->numblocks);
#endif


    if ((ret = malloc(sizeof(int))) == NULL)
        goto cleanup;
    *ret = -1;


    if ((buf = malloc(sizeof(unsigned char) * p->block_size)) == NULL)
        goto cleanup;
    if ((tag = malloc(sizeof(unsigned char) * p->tag_size)) == NULL)
        goto cleanup;


    block = arg->index;
    for (i = 0; i < arg->numblocks; i++) {
        memset(buf, 0, p->block_size);
        memset(tag, 0, p->tag_size);

#ifdef _PDP_DEBUG
    DEBUG(1, "\n Tagging block %02d", block);
#endif


        fseek(arg->file, block * p->block_size, SEEK_SET);
        fread(buf, 1, p->block_size, arg->file);
        if (ferror(arg->file)) goto cleanup;


        if (macpdp_tag_block(ctx, arg->key, buf, block, tag, &tag_len) != 0)
            goto cleanup;


        memcpy((arg->tags + (p->tag_size * block)), tag, tag_len);

        block += ctx->num_threads;
    }
    *ret = 0;

cleanup:
    if (!ret || (ret && *ret))
        PDP_ERR("some thread was unable to create a tag.");
    sfree(buf, sizeof(unsigned char) * p->block_size);
    sfree(tag, sizeof(unsigned char) * p->tag_size);
#ifdef _THREAD_SUPPORT
    if (ctx->num_threads > 1)
        pthread_exit(ret);
#endif
    return ret;
}
