md5_finish_text(md5_state_t *pms, char *buf, int allow_at)
{
	static const char chars[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_@";
	md5_byte_t digest[16];
	char *initial_buf = buf;
	int bit;

	md5_finish(pms, digest);
	for (bit = 0; bit < MD5_DIGEST_SIZE * 8; bit += 6) {
		int first_char = bit / 8;
		int val = digest[first_char] >> (bit % 8);
		if (bit + 8 > (first_char + 1) * 8 && first_char < MD5_DIGEST_SIZE - 1)
			val += digest[first_char + 1] << (8 - (bit % 8));
		if ((val & 0x3F) == 0x3F && !allow_at) {
			val = 0x1F;
			bit--;
		}
		*buf++ = chars[val & 0x3F];
	}
	return buf - initial_buf;
}
