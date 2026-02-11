atihdmi_paired_chmap_cea_alloc_validate_get_type(struct cea_channel_speaker_allocation *cap,
							    int channels)
{
	int c;


	int chanpairs = 0;


	if ((channels % 2) != 0)
		return -1;

	for (c = 0; c < 7; c += 2) {
		if (cap->speakers[c] || cap->speakers[c+1])
			chanpairs++;
	}

	if (chanpairs * 2 != channels)
		return -1;

	return SNDRV_CTL_TLVT_CHMAP_PAIRED;
}
