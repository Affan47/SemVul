apdp_write_tags_to_file(const pdp_ctx_t *ctx, const pdp_apdp_tagdata_t* t)
{
    unsigned char *buf = NULL;
    FILE *tagfile = NULL;
    unsigned int len = 0;
    size_t off = 0;
    int status = -1;

    if (!ctx || !t || !t->tags || !t->tags_num ||
                !t->tags_size || !ctx->ofilepath)
        return -1;

    if ((access(ctx->ofilepath, F_OK) == 0) && (ctx->verbose)) {
        PDP_ERR("WARNING: overwriting [%s]", ctx->ofilepath);
    }
    if ((tagfile = fopen(ctx->ofilepath, "w")) == NULL){
        PDP_ERR("%d", ferror(tagfile));
        PDP_ERR("unable to create %s", ctx->ofilepath);
        goto cleanup;
    }

    if ((apdp_serialize_tags(ctx, t, &buf, &len)) != 0) goto cleanup;
    do {
        off += fwrite(buf + off, 1, len, tagfile);
        if (ferror(tagfile)) goto cleanup;

    } while (off < len);
    status = 0;

cleanup:
    sfree(buf, len);
    if (tagfile) fclose(tagfile);
    return status;
}
