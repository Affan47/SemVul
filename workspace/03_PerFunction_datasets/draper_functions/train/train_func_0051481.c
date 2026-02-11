formants_reduce_hf(frame_t *fr, int level)
{

	int  ix;
	int  x;

	if(voice->klattv[0])
		return;

	for(ix=2; ix < 8; ix++)
	{
		x = fr->fheight[ix] * level;
		fr->fheight[ix] = x/100;
	}
}
