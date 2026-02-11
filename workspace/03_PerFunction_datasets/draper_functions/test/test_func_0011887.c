oss_setformat(struct oss_handle *h, struct ng_audio_fmt *fmt)
{
    int frag;

    if (0 == afmt_to_oss[fmt->fmtid])
	return -1;

    h->afmt     = afmt_to_oss[fmt->fmtid];
    h->channels = ng_afmt_to_channels[fmt->fmtid];
    frag        = 0x7fff000c;


    ioctl(h->fd, SNDCTL_DSP_SETFMT, &h->afmt);
    if (h->afmt != afmt_to_oss[fmt->fmtid]) {
	if (ng_debug)
	    fprintf(stderr,"oss: SNDCTL_DSP_SETFMT(%d): %s\n",
		    afmt_to_oss[fmt->fmtid],strerror(errno));
	goto err;
    }


    ioctl(h->fd, SNDCTL_DSP_CHANNELS, &h->channels);
    if (h->channels != ng_afmt_to_channels[fmt->fmtid]) {
	if (ng_debug)
	    fprintf(stderr,"oss: SNDCTL_DSP_CHANNELS(%d): %s\n",
		    ng_afmt_to_channels[fmt->fmtid],strerror(errno));
	goto err;
    }


    h->rate = fmt->rate;
    ioctl(h->fd, SNDCTL_DSP_SPEED, &h->rate);
    ioctl(h->fd, SNDCTL_DSP_SETFRAGMENT, &frag);
    if (h->rate != fmt->rate) {
	fprintf(stderr, "oss: warning: got sample rate %d (asked for %d)\n",
		h->rate,fmt->rate);
	if (h->rate < fmt->rate * 1001 / 1000 &&
	    h->rate > fmt->rate *  999 / 1000) {

	    h->rate = fmt->rate;
	}
    }

    if (-1 == ioctl(h->fd, SNDCTL_DSP_GETBLKSIZE,  &h->blocksize)) {
	if (ng_debug)
	    perror("SNDCTL_DSP_GETBLKSIZE");
	goto err;
    }
    if (0 == h->blocksize)

	h->blocksize = 4096;

    if (ng_debug)
	fprintf(stderr,"oss: bs=%d rate=%d channels=%d bits=%d (%s)\n",
		h->blocksize,h->rate,
		ng_afmt_to_channels[fmt->fmtid],
		ng_afmt_to_bits[fmt->fmtid],
		ng_afmt_to_desc[fmt->fmtid]);
    return 0;

 err:
    if (ng_debug)
	fprintf(stderr,"oss: sound format not supported [%s]\n",
		ng_afmt_to_desc[fmt->fmtid]);
    return -1;
}
