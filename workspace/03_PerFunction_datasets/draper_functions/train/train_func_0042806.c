mpg123_fmt_all(mpg123_pars *mp)
{
	size_t rate, ch, enc;
	if(mp == NULL) return MPG123_BAD_PARS;

	if(PVERB(mp,3)) fprintf(stderr, "Note: Enabling all formats.\n");

	for(ch=0;   ch   < NUM_CHANNELS;     ++ch)
	for(rate=0; rate < MPG123_RATES+1;   ++rate)
	for(enc=0;  enc  < MPG123_ENCODINGS; ++enc)
	mp->audio_caps[ch][rate][enc] = good_enc(my_encodings[enc]) ? 1 : 0;

	return MPG123_OK;
}
