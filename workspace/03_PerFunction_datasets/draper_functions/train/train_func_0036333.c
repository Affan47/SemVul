krb5_k_encrypt(krb5_context context, krb5_key key,
               krb5_keyusage usage, const krb5_data *cipher_state,
               const krb5_data *input, krb5_enc_data *output)
{
    const struct krb5_keytypes *ktp;
    krb5_crypto_iov iov[4];
    krb5_error_code ret;
    unsigned int header_len, padding_len, trailer_len, total_len;

    ktp = find_enctype(key->keyblock.enctype);
    if (ktp == NULL)
        return KRB5_BAD_ENCTYPE;

    output->magic = KV5M_ENC_DATA;
    output->kvno = 0;
    output->enctype = key->keyblock.enctype;


    header_len = ktp->crypto_length(ktp, KRB5_CRYPTO_TYPE_HEADER);
    padding_len = krb5int_c_padding_length(ktp, input->length);
    trailer_len = ktp->crypto_length(ktp, KRB5_CRYPTO_TYPE_TRAILER);
    total_len = header_len + input->length + padding_len + trailer_len;
    if (output->ciphertext.length < total_len)
        return KRB5_BAD_MSIZE;


    iov[0].flags = KRB5_CRYPTO_TYPE_HEADER;
    iov[0].data = make_data(output->ciphertext.data, header_len);

    iov[1].flags = KRB5_CRYPTO_TYPE_DATA;
    iov[1].data = make_data(output->ciphertext.data + header_len,
                            input->length);
    if (input->length > 0)
        memcpy(iov[1].data.data, input->data, input->length);

    iov[2].flags = KRB5_CRYPTO_TYPE_PADDING;
    iov[2].data = make_data(iov[1].data.data + input->length, padding_len);

    iov[3].flags = KRB5_CRYPTO_TYPE_TRAILER;
    iov[3].data = make_data(iov[2].data.data + padding_len, trailer_len);

    ret = ktp->encrypt(ktp, key, usage, cipher_state, iov, 4);
    if (ret != 0)
        zap(iov[1].data.data, iov[1].data.length);
    else
        output->ciphertext.length = total_len;
    return ret;
}
