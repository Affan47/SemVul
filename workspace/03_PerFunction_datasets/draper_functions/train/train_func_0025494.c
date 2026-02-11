pm3393_set_mtu(struct cmac *cmac, int mtu)
{
	int enabled = cmac->instance->enabled;


	mtu += 14 + 4;
	if (mtu > MAX_FRAME_SIZE)
		return -EINVAL;


	if (enabled)
		pm3393_disable(cmac, MAC_DIRECTION_RX | MAC_DIRECTION_TX);

	pmwrite(cmac, SUNI1x10GEXP_REG_RXXG_MAX_FRAME_LENGTH, mtu);
	pmwrite(cmac, SUNI1x10GEXP_REG_TXXG_MAX_FRAME_SIZE, mtu);

	if (enabled)
		pm3393_enable(cmac, enabled);
	return 0;
}
