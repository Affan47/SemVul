WavegenFile2(void)
{
	int finished;
	unsigned char wav_outbuf[1024];

	out_ptr = out_start = wav_outbuf;
	out_end = wav_outbuf + sizeof(wav_outbuf);

	finished = WavegenFill(0);

	if(f_wave != NULL)
	{
		fwrite(wav_outbuf, 1, out_ptr-wav_outbuf, f_wave);
	}
	return(finished);
}
