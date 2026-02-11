krb5_oscontext_internalize(krb5_context kcontext, krb5_pointer *argp, krb5_octet **buffer, size_t *lenremain)
{
    krb5_error_code     kret;
    krb5_os_context     os_ctx;
    krb5_int32          ibuf;
    krb5_octet          *bp;
    size_t              remain;

    bp = *buffer;
    remain = *lenremain;
    kret = EINVAL;
    os_ctx = (krb5_os_context) NULL;

    if (krb5_ser_unpack_int32(&ibuf, &bp, &remain))
        ibuf = 0;
    if (ibuf == KV5M_OS_CONTEXT) {
        kret = ENOMEM;


        if ((os_ctx = (krb5_os_context)
             calloc(1, sizeof(struct _krb5_os_context))) &&
            (remain >= 4*sizeof(krb5_int32))) {
            os_ctx->magic = KV5M_OS_CONTEXT;


            (void) krb5_ser_unpack_int32(&os_ctx->time_offset, &bp, &remain);
            (void) krb5_ser_unpack_int32(&os_ctx->usec_offset, &bp, &remain);
            (void) krb5_ser_unpack_int32(&os_ctx->os_flags, &bp, &remain);
            (void) krb5_ser_unpack_int32(&ibuf, &bp, &remain);

            if (ibuf == KV5M_OS_CONTEXT) {
                os_ctx->magic = KV5M_OS_CONTEXT;
                kret = 0;
                *buffer = bp;
                *lenremain = remain;
            } else
                kret = EINVAL;
        }
    }
    if (!kret) {
        *argp = (krb5_pointer) os_ctx;
    }
    else {
        if (os_ctx)
            free(os_ctx);
    }
    return(kret);
}
