kg_translate_iov(krb5_context context, int proto, int dce_style, size_t ec,
                 size_t rrc, krb5_enctype enctype, gss_iov_buffer_desc *iov,
                 int iov_count, krb5_crypto_iov **pkiov, size_t *pkiov_count)
{
    return proto ?
        kg_translate_iov_v3(context, dce_style, ec, rrc, enctype,
                            iov, iov_count, pkiov, pkiov_count) :
        kg_translate_iov_v1(context, enctype, iov, iov_count,
                            pkiov, pkiov_count);
}
