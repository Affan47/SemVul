mac_method_hmac_ripemd160_hash(LIBSSH2_SESSION * session,
                               unsigned char *buf, uint32_t seqno,
                               const unsigned char *packet,
                               uint32_t packet_len,
                               const unsigned char *addtl,
                               uint32_t addtl_len,
                               void **abstract)
{
    libssh2_hmac_ctx ctx;
    unsigned char seqno_buf[4];
    (void) session;

    _libssh2_htonu32(seqno_buf, seqno);

    libssh2_hmac_ripemd160_init(&ctx, *abstract, 20);
    libssh2_hmac_update(ctx, seqno_buf, 4);
    libssh2_hmac_update(ctx, packet, packet_len);
    if (addtl && addtl_len) {
        libssh2_hmac_update(ctx, addtl, addtl_len);
    }
    libssh2_hmac_final(ctx, buf);
    libssh2_hmac_cleanup(&ctx);

    return 0;
}
