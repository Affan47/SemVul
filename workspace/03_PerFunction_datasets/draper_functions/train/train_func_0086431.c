mpeg_get_audio_rate(unsigned char *header)
{
    int rate = 44100;

    if (mpeg_getbits(header,12,1) == 1) {

	switch (mpeg_getbits(header,20,2)) {
	case 0: rate  = 44100; break;
	case 1: rate  = 48000; break;
	case 2: rate  = 32000; break;
	}
	if (ng_debug)
	    fprintf(stderr,"mpeg: MPEG1 audio, rate %d\n",rate);
    } else {

	switch (mpeg_getbits(header,20,2)) {
	case 0: rate  = 22050; break;
	case 1: rate  = 24000; break;
	case 2: rate  = 16000; break;
	}
	if (ng_debug)
	    fprintf(stderr,"mpeg: MPEG2 audio, rate %d\n",rate);
    }
    return rate;
}
