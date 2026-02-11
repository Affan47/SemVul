snd_atiixp_check_bus_busy(struct atiixp *chip)
{
	unsigned int bus_busy;
	if (atiixp_read(chip, CMD) & (ATI_REG_CMD_SEND_EN |
				      ATI_REG_CMD_RECEIVE_EN |
				      ATI_REG_CMD_SPDF_OUT_EN))
		bus_busy = ATI_REG_IER_SET_BUS_BUSY;
	else
		bus_busy = 0;
	atiixp_update(chip, IER, ATI_REG_IER_SET_BUS_BUSY, bus_busy);
}
