dai_set_srt_msr(struct dai *dai, unsigned int msr)
{
	unsigned int rsr;

	for (rsr = 0; msr > 1; msr >>= 1)
		rsr++;

	dai->hw->dai_srt_set_rsr(dai->ctrl_blk, rsr);
	return 0;
}
