iscsit_do_crypto_hash_buf(
	struct hash_desc *hash,
	const void *buf,
	u32 payload_length,
	u32 padding,
	u8 *pad_bytes,
	u8 *data_crc)
{
	struct scatterlist sg;

	crypto_hash_init(hash);

	sg_init_one(&sg, buf, payload_length);
	crypto_hash_update(hash, &sg, payload_length);

	if (padding) {
		sg_init_one(&sg, pad_bytes, padding);
		crypto_hash_update(hash, &sg, padding);
	}
	crypto_hash_final(hash, data_crc);
}
