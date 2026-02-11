process (const AES_KEY* key, const uint8_t* in, uint8_t* out, size_t len)
{
	for (size_t i = 0; i < len; ++i) {
		if (byte_counter % 16 == 0) {


			uint8_t		ctr[16];
			uint32_t	blockno = htonl(byte_counter / 16);
			memcpy(ctr, nonce, 12);
			memcpy(ctr + 12, &blockno, 4);
			AES_encrypt(ctr, otp, key);
		}


		out[i] = in[i] ^ otp[byte_counter++ % 16];
	}
}
