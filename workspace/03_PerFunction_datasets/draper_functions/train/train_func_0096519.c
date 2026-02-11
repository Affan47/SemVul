get_next_code(void) {
	ILint	i, t;
	ILuint	ret;


	if (!nbits_left) {
		if (navail_bytes <= 0) {
			pbytes = byte_buff;
			navail_bytes = igetc();

			if(navail_bytes == IL_EOF) {
				success = IL_FALSE;
				return ending;
			}

			if (navail_bytes) {
				for (i = 0; i < navail_bytes; i++) {
					if((t = igetc()) == IL_EOF) {
						success = IL_FALSE;
						return ending;
					}
					byte_buff[i] = t;
				}
			}
		}
		b1 = *pbytes++;
		nbits_left = 8;
		navail_bytes--;
	}

	ret = b1 >> (8 - nbits_left);
	while (curr_size > nbits_left) {
		if (navail_bytes <= 0) {
			pbytes = byte_buff;
			navail_bytes = igetc();

			if(navail_bytes == IL_EOF) {
				success = IL_FALSE;
				return ending;
			}

			if (navail_bytes) {
				for (i = 0; i < navail_bytes; i++) {
					if((t = igetc()) == IL_EOF) {
						success = IL_FALSE;
						return ending;
					}
					byte_buff[i] = t;
				}
			}
		}
		b1 = *pbytes++;
		ret |= b1 << nbits_left;
		nbits_left += 8;
		navail_bytes--;
	}
	nbits_left -= curr_size;

	return (ret & code_mask[curr_size]);
}
