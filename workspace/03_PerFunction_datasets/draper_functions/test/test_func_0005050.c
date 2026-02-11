gf_rtp_get_current_time(GF_RTPChannel *ch)
{
	Double ret;
	if (!ch) return 0.0;
	ret = (Double) ch->CurrentTime;
	ret -= (Double) ch->rtp_time;
	ret /= ch->TimeScale;
	return ret;
}
