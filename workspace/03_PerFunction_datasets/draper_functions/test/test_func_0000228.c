decode_ADPCM_4_sample(uint8 sample,
								 int& reference,
								 int& scale)
{
	static int scaleMap[8] = { -2, -1, 0, 0, 1, 1, 1, 1 };

	if (sample & 0x08) {
		reference = max(0x00, reference - ((sample & 0x07) << scale));
	} else {
		reference = min(0xff, reference + ((sample & 0x07) << scale));
	}

	scale = max(2, min(6, scaleMap[sample & 0x07]));

	return reference;
}
