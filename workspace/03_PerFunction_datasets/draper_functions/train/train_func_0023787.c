chap_encode_string(uint8_t *intnum, int buf_len, char *encode_buf, int encoding_fmt)
{
	encode_buf[0] = '0';
	if (encoding_fmt == HEX_FORMAT) {
		encode_buf[1] = 'x';
		encode_hex_string(intnum, buf_len, encode_buf + 2);
	} else if (encoding_fmt == BASE64_FORMAT) {
		encode_buf[1] = 'b';
		encode_base64_string(intnum, buf_len, encode_buf + 2);
	}
}
