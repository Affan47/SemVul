wav_read_open(const char *filename) {
	struct wav_reader* wr = (struct wav_reader*) malloc(sizeof(*wr));
	long data_pos = 0;
	memset(wr, 0, sizeof(*wr));

	wr->wav = fopen(filename, "rb");
	if (wr->wav == NULL) {
		free(wr);
		return NULL;
	}

	while (1) {
		uint32_t tag, tag2, length;
		tag = read_tag(wr);
		if (feof(wr->wav))
			break;
		length = read_int32(wr);
		if (tag != TAG('R', 'I', 'F', 'F') || length < 4) {
			fseek(wr->wav, length, SEEK_CUR);
			continue;
		}
		tag2 = read_tag(wr);
		length -= 4;
		if (tag2 != TAG('W', 'A', 'V', 'E')) {
			fseek(wr->wav, length, SEEK_CUR);
			continue;
		}

		while (length >= 8) {
			uint32_t subtag, sublength;
			subtag = read_tag(wr);
			if (feof(wr->wav))
				break;
			sublength = read_int32(wr);
			length -= 8;
			if (length < sublength)
				break;
			if (subtag == TAG('f', 'm', 't', ' ')) {
				if (sublength < 16) {

					break;
				}
				wr->format          = read_int16(wr);
				wr->channels        = read_int16(wr);
				wr->sample_rate     = read_int32(wr);
				wr->byte_rate       = read_int32(wr);
				wr->block_align     = read_int16(wr);
				wr->bits_per_sample = read_int16(wr);
				fseek(wr->wav, sublength - 16, SEEK_CUR);
			} else if (subtag == TAG('d', 'a', 't', 'a')) {
				data_pos = ftell(wr->wav);
				wr->data_length = sublength;
				fseek(wr->wav, sublength, SEEK_CUR);
			} else {
				fseek(wr->wav, sublength, SEEK_CUR);
			}
			length -= sublength;
		}
		if (length > 0) {

			fseek(wr->wav, length, SEEK_CUR);
		}
	}
	fseek(wr->wav, data_pos, SEEK_SET);
	return wr;
}
