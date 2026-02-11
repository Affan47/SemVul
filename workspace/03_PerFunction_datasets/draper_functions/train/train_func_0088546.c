pdp_write_data_to_s3(const pdp_ctx_t *ctx, const char* filepath,
                         unsigned char *data, unsigned int data_len)
{
#ifndef _S3_SUPPORT
    PDP_UNSUPPORTED("S3");
    return -1;
#else
    struct buffer_pointer bp;
    S3Status status = S3StatusErrorUnknown;

    if (!filepath || (strlen(filepath) >= MAXPATHLEN))
        return -1;

    bp.buf = data;
    bp.len = data_len;


    if (!s3_initialized) {
        status = S3_initialize("s3", S3_INIT_ALL, ctx->s3_hostname);
        if (status != S3StatusOK) {
            PDP_ERR("failed to initialize libs3: %s", S3_get_status_name(status));
            goto cleanup;
        }
        s3_initialized = 1;
        atexit(S3_deinitialize);
    }

    S3BucketContext bucketContext = {
        0,
        ctx->s3_bucket_name,
        ctx->s3_protocol,
        S3UriStylePath,
        ctx->s3_access_key,
        ctx->s3_secret_key
    };


    S3PutProperties putProperties = {
        0,
        0,
        0,
        0,


        0,


        (int64_t)-1,

        S3CannedAclPrivate,
        0,

        0
    };


    S3PutObjectHandler putObjectHandler = {
        { &responsePropertiesCallback, &responseCompleteCallback },
        &putObjectDataCallback
    };

    S3_put_object(&bucketContext, basename((char *)filepath), data_len,
                  &putProperties, 0, &putObjectHandler, &bp);
    return 0;

cleanup:
    return -1;
#endif
}
