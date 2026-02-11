tone2(int samplerate)
{
	static int counter, divisor, output;
	int frequency = tone2_vco(samplerate);

	if( (sound_latch_b & 15) != 15 )
	{
		counter -= frequency;
		while( counter <= 0 )
		{
			counter += samplerate;
			if( ++divisor == 16 )
			{
				divisor = sound_latch_b & 15;
				output ^= 1;
			}
		}
	}
	return output ? tone2_level : -tone2_level;
}
