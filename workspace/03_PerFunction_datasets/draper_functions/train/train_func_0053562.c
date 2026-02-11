kg_ctx_size(kcontext, arg, sizep)
    krb5_context        kcontext;
    krb5_pointer        arg;
    size_t              *sizep;
{
    krb5_error_code     kret;
    krb5_gss_ctx_id_rec *ctx;
    size_t              required;


    kret = EINVAL;
    if ((ctx = (krb5_gss_ctx_id_rec *) arg)) {
        required = 21*sizeof(krb5_int32);
        required += 2*sizeof(krb5_int64);
        required += sizeof(ctx->seed);

        kret = 0;
        if (!kret && ctx->here)
            kret = krb5_size_opaque(kcontext,
                                    KV5M_PRINCIPAL,
                                    (krb5_pointer) ctx->here->princ,
                                    &required);

        if (!kret && ctx->there)
            kret = krb5_size_opaque(kcontext,
                                    KV5M_PRINCIPAL,
                                    (krb5_pointer) ctx->there->princ,
                                    &required);

        if (!kret && ctx->subkey)
            kret = krb5_size_opaque(kcontext,
                                    KV5M_KEYBLOCK,
                                    (krb5_pointer) &ctx->subkey->keyblock,
                                    &required);

        if (!kret && ctx->enc)
            kret = krb5_size_opaque(kcontext,
                                    KV5M_KEYBLOCK,
                                    (krb5_pointer) &ctx->enc->keyblock,
                                    &required);

        if (!kret && ctx->seq)
            kret = krb5_size_opaque(kcontext,
                                    KV5M_KEYBLOCK,
                                    (krb5_pointer) &ctx->seq->keyblock,
                                    &required);

        if (!kret)
            kret = kg_oid_size(kcontext,
                               (krb5_pointer) ctx->mech_used,
                               &required);

        if (!kret && ctx->seqstate)
            kret = kg_queue_size(kcontext, ctx->seqstate, &required);

        if (!kret)
            kret = krb5_size_opaque(kcontext,
                                    KV5M_CONTEXT,
                                    (krb5_pointer) ctx->k5_context,
                                    &required);
        if (!kret)
            kret = krb5_size_opaque(kcontext,
                                    KV5M_AUTH_CONTEXT,
                                    (krb5_pointer) ctx->auth_context,
                                    &required);
        if (!kret && ctx->acceptor_subkey)
            kret = krb5_size_opaque(kcontext,
                                    KV5M_KEYBLOCK, (krb5_pointer)
                                    &ctx->acceptor_subkey->keyblock,
                                    &required);
        if (!kret && ctx->authdata) {
            krb5_int32 i;

            for (i = 0; !kret && ctx->authdata[i]; i++) {
                kret = krb5_size_opaque(kcontext,
                                        KV5M_AUTHDATA,
                                        (krb5_pointer)ctx->authdata[i],
                                        &required);
            }
        }
        if (!kret) {
            krb5_gss_name_t initiator_name;

            initiator_name = ctx->initiate ? ctx->here : ctx->there;

            if (initiator_name && initiator_name->ad_context) {
                kret = krb5_size_opaque(kcontext,
                                        KV5M_AUTHDATA_CONTEXT,
                                        initiator_name->ad_context,
                                        &required);
            }
        }
        *sizep += required;
    }
    return(kret);
}
