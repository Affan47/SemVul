atiixp_in_enable_transfer(struct atiixp_modem *chip, int on)
{
	if (on) {
		unsigned int data = atiixp_read(chip, CMD);
		if (! (data & ATI_REG_CMD_MODEM_RECEIVE_EN)) {
			data |= ATI_REG_CMD_MODEM_RECEIVE_EN;
			atiixp_write(chip, CMD, data);
		}
	} else
		atiixp_update(chip, CMD, ATI_REG_CMD_MODEM_RECEIVE_EN, 0);
}
