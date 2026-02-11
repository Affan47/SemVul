v1_sign_message(gss_buffer_t in,
		RC4_KEY *signkey,
		uint32_t seq,
		unsigned char out[16])
{
    unsigned char sigature[12];
    uint32_t crc;

    _krb5_crc_init_table();
    crc = _krb5_crc_update(in->value, in->length, 0);

    encode_le_uint32(0, &sigature[0]);
    encode_le_uint32(crc, &sigature[4]);
    encode_le_uint32(seq, &sigature[8]);

    encode_le_uint32(1, out);
    RC4(signkey, sizeof(sigature), sigature, out + 4);

    if (RAND_bytes(out + 4, 4) != 1)
	return GSS_S_UNAVAILABLE;

    return 0;
}
