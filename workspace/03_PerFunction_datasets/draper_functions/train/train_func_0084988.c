base64_decode(const char *data,
					int input_length,
					int *output_length)
{
	if (decoding_table == NULL) {
		build_decoding_table();
	}

	if (input_length % 4 != 0) {
		return NULL;
	}

	*output_length = input_length / 4 * 3;
	if (data[input_length - 1] == '=') {
		(*output_length)--;
	}
	if (data[input_length - 2] == '=') {
		(*output_length)--;
	}

	unsigned char *decoded_data = (unsigned char *)malloc(*output_length);
	if (decoded_data == NULL) {
		return NULL;
	}

	for (int i = 0, j = 0; i < input_length;) {
		uint32_t sextet_a = data[i] == '=' ? 0 & i++ : decoding_table[(int)data[i++]];
		uint32_t sextet_b = data[i] == '=' ? 0 & i++ : decoding_table[(int)data[i++]];
		uint32_t sextet_c = data[i] == '=' ? 0 & i++ : decoding_table[(int)data[i++]];
		uint32_t sextet_d = data[i] == '=' ? 0 & i++ : decoding_table[(int)data[i++]];

		uint32_t triple = (sextet_a << 3 * 6)
								+ (sextet_b << 2 * 6)
								+ (sextet_c << 1 * 6)
								+ (sextet_d << 0 * 6);

		if (j < *output_length) {
			decoded_data[j++] = (triple >> 2 * 8) & 0xFF;
		}
		if (j < *output_length) {
			decoded_data[j++] = (triple >> 1 * 8) & 0xFF;
		}
		if (j < *output_length) {
			decoded_data[j++] = (triple >> 0 * 8) & 0xFF;
		}
	}

	return decoded_data;
}
