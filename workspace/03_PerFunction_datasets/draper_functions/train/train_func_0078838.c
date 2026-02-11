mpg123_fmt(mpg123_pars *mp, long rate, int channels, int encodings)
{
	int ie, ic, ratei;
	int ch[2] = {0, 1};
	if(mp == NULL) return MPG123_BAD_PARS;
	if(!(channels & (MPG123_MONO|MPG123_STEREO))) return MPG123_BAD_CHANNEL;

	if(PVERB(mp,3)) fprintf(stderr, "Note: Want to enable format %li/%i for encodings 0x%x.\n", rate, channels, encodings);

	if(!(channels & MPG123_STEREO)) ch[1] = 0;
	else if(!(channels & MPG123_MONO)) ch[0] = 1;
	ratei = rate2num(mp, rate);
	if(ratei < 0) return MPG123_BAD_RATE;


	for(ic = 0; ic < 2; ++ic)
	{
		for(ie = 0; ie < MPG123_ENCODINGS; ++ie)
		if(good_enc(my_encodings[ie]) && ((my_encodings[ie] & encodings) == my_encodings[ie]))
		mp->audio_caps[ch[ic]][ratei][ie] = 1;

		if(ch[0] == ch[1]) break;
	}

	return MPG123_OK;
}
