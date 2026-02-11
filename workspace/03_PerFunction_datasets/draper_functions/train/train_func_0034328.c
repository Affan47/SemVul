decode_rle(unsigned short* raw_data, unsigned short* output, int stop_count)
{
	unsigned int i = 0, o = 0;

	while (o < stop_count) {
		unsigned short sample = raw_data[i++];


		if (sample & 0x80) {
			unsigned short value = raw_data[i++];
			unsigned int count = sample - 0x7F;

			for (int j = 0; j < count; j++){
				output[o++] = value;
			}
		} else {
			unsigned int count = sample + 1;

			for (int j = 0; j < count; j++){
				output[o++] = raw_data[i++];
			}
		}
	}

	return i;
}
