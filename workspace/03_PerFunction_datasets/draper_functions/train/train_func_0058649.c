OKIM6295_set_bank_base(int which, int base)
{
	int channel;

	for (channel = 0; channel < OKIM6295_VOICES; channel++)
	{
		struct ADPCMVoice *voice = &adpcm[which * OKIM6295_VOICES + channel];


		stream_update(voice->stream, 0);
		okim6295_base[which][channel] = base;
	}
}
