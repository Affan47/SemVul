kg_queue_internalize(kcontext, argp, buffer, lenremain)
    krb5_context        kcontext;
    krb5_pointer        *argp;
    krb5_octet          **buffer;
    size_t              *lenremain;
{
    krb5_int32 ibuf;
    krb5_octet         *bp;
    size_t             remain;
    krb5_error_code    err;

    bp = *buffer;
    remain = *lenremain;


    if (krb5_ser_unpack_int32(&ibuf, &bp, &remain))
        return (EINVAL);

    if (ibuf != KV5M_GSS_QUEUE)
        return (EINVAL);

    err = g_queue_internalize(argp, &bp, &remain);
    if (err)
        return err;


    if (krb5_ser_unpack_int32(&ibuf, &bp, &remain)) {
        g_order_free(argp);
        return (EINVAL);
    }

    if (ibuf != KV5M_GSS_QUEUE) {
        g_order_free(argp);
        return (EINVAL);
    }

    *buffer = bp;
    *lenremain = remain;
    return 0;
}
