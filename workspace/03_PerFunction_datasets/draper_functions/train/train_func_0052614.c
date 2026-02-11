kirkwood_i2s_play_mute(unsigned ctl)
{
	if (!(ctl & KIRKWOOD_PLAYCTL_I2S_EN))
		ctl |= KIRKWOOD_PLAYCTL_I2S_MUTE;
	if (!(ctl & KIRKWOOD_PLAYCTL_SPDIF_EN))
		ctl |= KIRKWOOD_PLAYCTL_SPDIF_MUTE;
	return ctl;
}
