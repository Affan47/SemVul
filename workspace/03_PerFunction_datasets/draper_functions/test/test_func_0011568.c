channel_is_valid(RTPClient *rtp, RTPStream *ch)
{
	u32 i=0;
	RTPStream *st;
	while ((st = (RTPStream *)gf_list_enum(rtp->channels, &i))) {
		if (st == ch) return 1;
	}
	return 0;
}
