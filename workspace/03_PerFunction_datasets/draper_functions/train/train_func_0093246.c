usX2Y_pcms_busy_check(struct snd_card *card)
{
	struct usX2Ydev	*dev = usX2Y(card);
	int i;

	for (i = 0; i < dev->pcm_devs * 2; i++) {
		struct snd_usX2Y_substream *subs = dev->subs[i];
		if (subs && subs->pcm_substream &&
		    SUBSTREAM_BUSY(subs->pcm_substream))
			return -EBUSY;
	}
	return 0;
}
