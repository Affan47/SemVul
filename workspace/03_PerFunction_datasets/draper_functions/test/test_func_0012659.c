write_wavheader (struct zfile *wavfile, uae_u32 size, uae_u32 freq)
{
	uae_u16 tw;
	uae_u32 tl;
	int bits = 8, channels = 1;

	zfile_fseek (wavfile, 0, SEEK_SET);
	zfile_fwrite ("RIFF", 1, 4, wavfile);
	tl = 0;
	if (size)
		tl = size - 8;
	zfile_fwrite (&tl, 1, 4, wavfile);
	zfile_fwrite ("WAVEfmt ", 1, 8, wavfile);
	tl = 16;
	zfile_fwrite (&tl, 1, 4, wavfile);
	tw = 1;
	zfile_fwrite (&tw, 1, 2, wavfile);
	tw = channels;
	zfile_fwrite (&tw, 1, 2, wavfile);
	tl = freq;
	zfile_fwrite (&tl, 1, 4, wavfile);
	tl = freq * channels * bits / 8;
	zfile_fwrite (&tl, 1, 4, wavfile);
	tw = channels * bits / 8;
	zfile_fwrite (&tw, 1, 2, wavfile);
	tw = bits;
	zfile_fwrite (&tw, 1, 2, wavfile);
	zfile_fwrite ("data", 1, 4, wavfile);
	tl = 0;
	if (size)
		tl = size - 44;
	zfile_fwrite (&tl, 1, 4, wavfile);
}
