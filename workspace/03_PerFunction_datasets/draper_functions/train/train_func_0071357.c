nss_io_filter_output(ap_filter_t *f,
                                         apr_bucket_brigade *bb)
{
    apr_status_t status = APR_SUCCESS;
    nss_filter_ctx_t *filter_ctx = f->ctx;
    nspr_filter_in_ctx_t *inctx;
    nspr_filter_out_ctx_t *outctx;
    apr_read_type_e rblock = APR_NONBLOCK_READ;

    if (f->c->aborted) {
        apr_brigade_cleanup(bb);
        return APR_ECONNABORTED;
    }

    if (!filter_ctx->pssl) {

        return ap_pass_brigade(f->next, bb);
    }

    inctx = filter_ctx->inctx;
    outctx = filter_ctx->outctx;


    inctx->mode = AP_MODE_READBYTES;
    inctx->block = APR_BLOCK_READ;

    while (!APR_BRIGADE_EMPTY(bb)) {
        apr_bucket *bucket = APR_BRIGADE_FIRST(bb);


        if (APR_BUCKET_IS_EOS(bucket) || APR_BUCKET_IS_FLUSH(bucket)) {
            if (nspr_filter_out_flush(filter_ctx->outctx) < 0) {
                status = outctx->rc;
                break;
            }

            if (APR_BUCKET_IS_EOS(bucket)) {


                if ((status = ap_pass_brigade(f->next, bb)) != APR_SUCCESS) {
                    return status;
                }
                break;
            }
            else {


                apr_bucket_delete(bucket);
            }
        }
#if defined AP_BUCKET_IS_EOC
        else if (AP_BUCKET_IS_EOC(bucket)) {


            filter_ctx->nobuffer = 1;
            status = nss_filter_io_shutdown(filter_ctx, f->c, 0);
            if (status != APR_SUCCESS) {
                ap_log_error(APLOG_MARK, APLOG_INFO, status, f->c->base_server,
                             "SSL filter error shutting down I/O");
            }
            if ((status = ap_pass_brigade(f->next, bb)) != APR_SUCCESS) {
                return status;
            }
            break;
        }
#endif
        else {

            const char *data;
            apr_size_t len;

            status = apr_bucket_read(bucket, &data, &len, rblock);

            if (APR_STATUS_IS_EAGAIN(status)) {

                if (nspr_filter_out_flush(filter_ctx->outctx) < 0) {
                    status = outctx->rc;
                    break;
                }
                rblock = APR_BLOCK_READ;
                continue;
            }

            rblock = APR_NONBLOCK_READ;

            if (!APR_STATUS_IS_EOF(status) && (status != APR_SUCCESS)) {
                break;
            }

            status = nss_filter_write(f, data, len);
            apr_bucket_delete(bucket);

            if (status != APR_SUCCESS) {
                break;
            }
        }
    }
    return status;
}
